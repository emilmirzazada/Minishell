/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emirzaza <emirzaza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 22:09:23 by emirzaza          #+#    #+#             */
/*   Updated: 2023/10/31 19:41:03 by emirzaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(t_minishell *mini, t_cmd *cmd)
{
	long	value;
	bool	res;

	value = 0;
	res = true;
	if (cmd->args[1] || ft_strcmp(cmd->args[1], "0") == 0)
		res = ft_atoi(cmd->args[1], &value);
	else
		mini->exit_code = 0;
	if (!res)
	{
		ft_putstr_fd("exit\nexit: numeric argument required\n", 2);
		mini->exit_code = 255;
	}
	else if (cmd->args[1] && cmd->args[2])
	{
		ft_putstr_fd("exit\nexit: too many arguments\n", 2);
		return (mini->exit_code = 1, mini->exit_code);
	}
	else
		ft_putstr_fd("exit\n", 1);
	if (value != 0)
		mini->exit_code = value % 256;
	free_mini(mini);
	return (exit(mini->exit_code), mini->exit_code);
}
