/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emirzaza <emirzaza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 19:37:32 by emirzaza          #+#    #+#             */
/*   Updated: 2023/10/19 13:43:56 by emirzaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_commands(t_minishell *mini)
{
	t_cmd	*tmp;
	char	**tmp_args;
	t_file	*file;
	int		i;

	tmp = mini->cmd;
	i = 1;
	while (tmp)
	{
		printf("\n\n%d.NEW CMD, Name: %s\n", i++, tmp->name);
		tmp_args = tmp->args;
		printf("ARGS: ");
		while (*tmp_args)
		{
			printf("%s, ", *tmp_args);
			tmp_args++;
		}
		printf("\nFILES: ");
		file = tmp->files;
		while (file)
		{
			if (file->name)
				printf("Name: %s & token: %c,  ", file->name, file->token);
			if (file->delimeter)
				printf("Delimeter: %s & token: %c,  ", file->delimeter, file->token);
			file = file->next;
		}
		tmp = tmp->next;
	}
	printf("\n\n\n");
}

int	run_minishell(t_minishell *mini, char *input)
{
	mini->lex = NULL;
	mini->cmd = NULL;
	if (ft_lookup_input(mini, input))
		return (1);
	else
	{
		print_commands(mini);
		printf("EXIT_CODE = %d\n", execute_commands(mini));
		return (0);
	}
}

void	increase_shlvl(t_minishell *mini)
{
	t_env	*env;
	char	*env_val;
	long	shlvl;

	env_val = find_env(mini->env, "SHLVL");
	if (!env_val || !ft_atoi(env_val, &shlvl))
		shlvl = 0;
	shlvl++;
	env = ft_setenv(ft_strdup("SHLVL"), ft_itoa(shlvl));
	ft_envadd_back(&mini->env, env);
}

int	main(int ac, char **av, char **env)
{
	char				*input;
	t_minishell			mini;

	(void)ac;
	(void)av;
	ft_memset(&mini, 0, sizeof(mini));
	mini.env = ft_env_init(env);
	override_ctrl_echo();
	set_env_array(&mini);
	increase_shlvl(&mini);
	init_interactive_signals();
	while (1)
	{
		input = readline("Minishell: ");
		if (!input || ft_strcmp(input, "exit") == 0)
			free_mini(&mini);
		if (ft_strlen(input) > 0 && input[0] != '\0')
		{
			add_history(input);
			run_minishell(&mini, input);
		}
	}
	return (0);
}

// < input grep Hello | wc -l > out
// < input grep Hello | awk '{count++} END {print count}' > output
// ls > asd | grep input
// shllevel
// > $NAME
// afl++
// < input grep Hello | cat -e > out
// echo ''
// > >> out
//echo"hello"
//echo "hello">>>out
//echo "hello">>out
//handle pipes
//operator token in invalid combiantions (<<< , >>> , || , ...)
// echo "hello" <in | echo "hello world" >output | echo <infdkjgdkfgd
// refactor signals

// bash-3.2$ echo hello"world"
// helloworld
// bash-3.2$ echo hello"world$PWD"'"$PWD"'
// helloworld/Users/emirzaza/Desktop/42/CoreCurriculum/Projects"$PWD"
// bash-3.2$ echo hello"'world$PWD'"'"$PWD"'
// hello'world/Users/emirzaza/Desktop/42/CoreCurriculum/Projects'"$PWD"
// bash-3.2$ echo >|< hello
// bash: syntax error near unexpected token `<'
// bash-3.2$ echo >< hello
// bash: syntax error near unexpected token `<'
// bash-3.2$ 

//env > out | export
// ./minishell inside minishell gives command not found
// AND TEST INCREASE SHLVL AFTER FIXING THE ABOVE ONE