/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_executor.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrottger <wrottger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 17:10:42 by wrottger          #+#    #+#             */
/*   Updated: 2023/10/19 14:36:30 by wrottger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_builtin(t_minishell *mini)
{
	char	*name;

	name = mini->cmd->name;
	if (ft_strcmp(name, "env") == 0)
		return (ft_env(mini));
	if (ft_strcmp(name, "echo") == 0)
		return (ft_echo(mini->cmd));
	if (ft_strcmp(name, "cd") == 0)
		return (ft_cd(mini, mini->cmd));
	if (ft_strcmp(name, "pwd") == 0)
		return (ft_pwd());
	if (ft_strcmp(name, "export") == 0)
		return (ft_export(mini, mini->cmd));
	if (ft_strcmp(name, "unset") == 0)
		return (ft_unset(mini, mini->cmd));
	return (0);
}

int	is_builtin(char *name)
{
	if (!name)
		return (0);
	if (ft_strcmp(name, "env") == 0)
		return (1);
	if (ft_strcmp(name, "echo") == 0)
		return (1);
	if (ft_strcmp(name, "cd") == 0)
		return (1);
	if (ft_strcmp(name, "pwd") == 0)
		return (1);
	if (ft_strcmp(name, "export") == 0)
		return (1);
	if (ft_strcmp(name, "unset") == 0)
		return (1);
	return (0);
}
