/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mini.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrottger <wrottger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 11:18:38 by wrottger          #+#    #+#             */
/*   Updated: 2023/11/01 16:01:43 by wrottger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_mini(t_minishell *mini)
{
	if (mini->pids)
		free(mini->pids);
	if (mini->cmd)
		free_commands(mini->cmd);
	if (mini->split)
		free_splits(mini->split);
	if (mini->lex)
		free_lex(mini->lex);
	if (mini->env)
		free_env(mini->env);
	if (mini->env_arr)
		free_double_char(mini->env_arr);
	if (mini->input)
		free(mini->input);
	rl_clear_history();
}

void	clean_exit(t_minishell *mini, int exit_code)
{
	free_mini(mini);
	exit (exit_code);
}

void	perror_exit(char *str, t_minishell *mini, int exit_code)
{
	ft_putstr_fd("Minishell: ", 2);
	perror(str);
	free_mini(mini);
	exit(exit_code);
}
