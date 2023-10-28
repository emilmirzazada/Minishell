/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emirzaza <emirzaza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 19:37:32 by emirzaza          #+#    #+#             */
/*   Updated: 2023/10/28 11:57:30 by emirzaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reset_cmd(t_minishell *mini)
{
	if (mini->cmd)
		free_command(mini->cmd);
	if (mini->lex)
		free_lex(mini->lex);
	if (mini->split)
		free_splits(mini->split);
	mini->lex = NULL;
	mini->cmd = NULL;
	mini->split = NULL;
}

int	run_minishell(t_minishell *mini)
{
	add_history(mini->input);
	if (ft_lookup_input(mini))
		return (reset_cmd(mini), 1);
	mini->exit_code = execute_commands(mini);
	reset_cmd(mini);
	return (0);
}

void	handle_shlvl(t_minishell *mini)
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
	set_env_array(mini);
}

int	main(int ac, char **av, char **env)
{
	t_minishell			mini;

	(void)ac;
	(void)av;
	ft_bzero(&mini, sizeof(t_minishell));
	mini.env = ft_env_init(env);
	set_env_array(&mini);
	handle_shlvl(&mini);
	while (1)
	{
		init_interactive_signals();
		if (mini.input)
			free(mini.input);
		mini.input = NULL;
		if (g_signal_num != 0)
		{
			mini.exit_code = g_signal_num;
			g_signal_num = 0;
		}
		mini.input = readline("Minishell: ");
		if (!mini.input)
		{
			printf("exit\n");
			clean_exit(&mini, 0);
		}
		if (ft_strlen(mini.input) > 0 && mini.input[0] != '\0')
			run_minishell(&mini);
	}
	return (mini.exit_code);
}
