/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mini.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrottger <wrottger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 11:18:38 by wrottger          #+#    #+#             */
/*   Updated: 2023/10/17 11:35:21 by wrottger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_command(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->args[i])
		free(cmd->args[i++]);
	free(cmd->args);
	free(cmd);
	cmd = NULL;
}

static void	free_commands(t_cmd *list)
{
	t_cmd	*tmp;

	while (list)
	{
		tmp = list;
		list = list->next;
		free_command(tmp);
	}
}

void	free_mini(t_minishell *mini)
{
	if (mini->cmd)
		free_commands(mini->cmd);
}

void	perror_exit(char *str, t_minishell *mini, int exit_code)
{
	ft_putstr_fd("minishell: ", 2);
	perror(str);
	free_mini(mini);
	exit(exit_code);
}
