/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrottger <wrottger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 19:37:32 by emirzaza          #+#    #+#             */
/*   Updated: 2023/10/19 17:32:12 by wrottger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	run_minishell(t_minishell *mini, char *input)
{
	add_history(input);
	mini->lex = NULL;
	mini->cmd = NULL;
	if (ft_lookup_input(mini, input))
		return (1);
	execute_commands(mini);
	return (0);
}

void	handle_shlvl(t_minishell *mini, int flag)
{
	t_env	*env;
	char	*env_val;
	long	shlvl;

	env_val = find_env(mini->env, "SHLVL");
	if (!env_val || !ft_atoi(env_val, &shlvl))
		shlvl = 0;
	if (flag == 1)
		shlvl++;
	else if (flag == -1 && shlvl > 0)
		shlvl--;
	env = ft_setenv(ft_strdup("SHLVL"), ft_itoa(shlvl));
	ft_envadd_back(&mini->env, env);
	set_env_array(mini);
}

int	main(int ac, char **av, char **env)
{
	char				*input;
	t_minishell			mini;

	(void)ac;
	(void)av;
	ft_memset(&mini, 0, sizeof(mini));
	mini.env = ft_env_init(env);
	set_env_array(&mini);
	handle_shlvl(&mini, 1);
	init_interactive_signals();
	while (1)
	{
		input = readline("Minishell: ");
		if (!input)
		{
			handle_shlvl(&mini, -1);
			clean_exit(&mini, 0);
		}
		if (ft_strlen(input) > 0 && input[0] != '\0')
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