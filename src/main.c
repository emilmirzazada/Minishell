/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emirzaza <emirzaza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 19:37:32 by emirzaza          #+#    #+#             */
/*   Updated: 2023/10/24 18:39:38 by emirzaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	run_minishell(t_minishell *mini)
{
	add_history(mini->input);
	if (ft_lookup_input(mini))
		return (1);
	g_exit_code = execute_commands(mini);
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
	init_interactive_signals();
	while (1)
	{
		mini.input = readline("Minishell: ");
		if (!mini.input)
		{
			printf("exit\n");
			clean_exit(&mini, 0);
		}
		if (ft_strlen(mini.input) > 0 && mini.input[0] != '\0')
			run_minishell(&mini);
	}
	return (0);
}
