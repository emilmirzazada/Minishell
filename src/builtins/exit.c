/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrottger <wrottger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 22:09:23 by emirzaza          #+#    #+#             */
/*   Updated: 2023/10/27 19:20:24 by wrottger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(t_minishell *mini, t_cmd *cmd)
{
	long	value;
	bool	res;

	value = 0;
	res = true;
	if (cmd->args[1])
		res = ft_atoi(cmd->args[1], &value);
	else
		mini->exit_code = 0;
	printf("exit\n");
	if (!res)
	{
		ft_putstr_fd("exit: numeric argument required\n", 2);
		mini->exit_code = 255;
	}
	else if (cmd->args[1] && cmd->args[2])
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		mini->exit_code = 1;
		return (mini->exit_code);
	}
	if (value != 0)
		mini->exit_code = value % 256;
	free_mini(mini);
	return (exit(mini->exit_code), mini->exit_code);
}
