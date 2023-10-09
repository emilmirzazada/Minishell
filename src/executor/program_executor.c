/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program_executor.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrottger <wrottger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 08:38:10 by wrottger          #+#    #+#             */
/*   Updated: 2023/10/06 09:28:28 by wrottger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_program(
	t_minishell *mini,
	int command_count,
	int *pipe_fds,
	int j)
{
	char const	*pwd;
	char const	*path;

	pwd = find_env(mini->env, "PWD");
	path = find_env(mini->env, "PATH");
	mini->cmd->path = get_executable_path(*mini->cmd, pwd, path);
	if (execve(mini->cmd->path, mini->cmd->args, mini->cmd->args) < 0)
	{
		perror(*mini->cmd->args);
		exit(EXIT_FAILURE);
	}
	return (0);
}
