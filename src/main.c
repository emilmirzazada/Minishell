/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emirzaza <emirzaza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 19:37:32 by emirzaza          #+#    #+#             */
/*   Updated: 2023/10/15 18:36:21 by emirzaza         ###   ########.fr       */
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

int	main(int ac, char **av, char **env)
{
	char				*input;
	t_minishell			mini;

	(void)ac;
	(void)av;
	ft_memset(&mini, 0, sizeof(mini));
	ft_env_init(&mini, env);
	override_ctrl_echo();
	set_env_array(&mini);
	while (1)
	{
		input = readline("Minishell: ");
		init_interactive_signals();
		if (ft_strlen(input) > 0)
			add_history(input);
		if (!input)
			exit_minishell(input);
		run_minishell(&mini, input);
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
