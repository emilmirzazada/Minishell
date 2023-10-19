/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_executor.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrottger <wrottger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 17:10:42 by wrottger          #+#    #+#             */
/*   Updated: 2023/10/19 17:57:56 by wrottger         ###   ########.fr       */
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
	if (ft_strcmp(name, "exit") == 0)
		return (ft_exit(mini, mini->cmd));
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
	if (ft_strcmp(name, "exit") == 0)
		return (1);
	return (0);
}

int	execute_single_builtin(t_minishell *mini, int *pipe_fds, int command_count)
{
	int	status;

	save_stdio(mini->std_io);
	configure_pipes(mini, pipe_fds, 0);
	if (clean_pipes(pipe_fds, command_count * 2) == -1)
		perror_exit("Couldn't close pipes", mini, EXIT_FAILURE);
	status = execute_builtin(mini);
	load_stdio(mini->std_io);
	return (status);
}
