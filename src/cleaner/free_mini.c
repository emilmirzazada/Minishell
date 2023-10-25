/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mini.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emirzaza <emirzaza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 11:18:38 by wrottger          #+#    #+#             */
/*   Updated: 2023/10/24 21:07:55 by emirzaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static void	free_splits(t_split *list)
{
	t_split	*tmp;

	while (list)
	{
		tmp = list;
		list = list->next;
		free(tmp->arg);
		free(tmp);
		tmp = NULL;
	}
}

void	free_mini(t_minishell *mini)
{
	if (mini->cmd)
		free_commands(mini->cmd);
	if (mini->split)
		free_commands(mini->split);
}

void	clean_exit(t_minishell *mini, int exit_code)
{
	free_mini(mini);
	exit (exit_code);
}

void	perror_exit(char *str, t_minishell *mini, int exit_code)
{
	ft_putstr_fd("minishell: ", 2);
	perror(str);
	free_mini(mini);
	exit(exit_code);
}
