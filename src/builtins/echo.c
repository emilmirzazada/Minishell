/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emirzaza <emirzaza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 11:23:09 by emirzaza          #+#    #+#             */
/*   Updated: 2023/10/23 17:18:43 by emirzaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo_no_args(t_cmd *cmd)
{
	if (!cmd->args[1])
	{
		printf("\n");
		return (0);
	}
	else if (ft_strcmp(cmd->args[1], "-n") == 0
		&& !cmd->args[2])
		return (1);
	return (0);
}

int	echo_with_new_line(t_cmd *cmd)
{
	int	i;

	i = 1;
	while (cmd->args[i])
	{
		if (i > 1)
			ft_putstr_fd(" ", 1);
		ft_putstr_fd(cmd->args[i++], 1);
	}
	ft_putstr_fd("\n", 1);
	return (0);
}

int	echo_without_new_line(t_cmd *cmd)
{
	int	i;

	i = 2;
	while (cmd->args[i])
	{
		if (i > 2)
			ft_putstr_fd(" ", 1);
		ft_putstr_fd(cmd->args[i++], 1);
	}
	return (0);
}

int	ft_echo(t_cmd *cmd)
{
	if (echo_no_args(cmd))
		return (1);
	else if (cmd->args[1]
		&& ft_strcmp(cmd->args[1], "-n") == 0)
		echo_without_new_line(cmd);
	else
		echo_with_new_line(cmd);
	return (0);
}
