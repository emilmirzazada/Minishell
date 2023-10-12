/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program_executor.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrottger <wrottger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 08:38:10 by wrottger          #+#    #+#             */
/*   Updated: 2023/10/12 11:27:15 by wrottger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_program(t_minishell *mini)
{
	char	*pwd;
	char	*path;

	pwd = find_env(mini->env, "PWD");
	path = find_env(mini->env, "PATH");
	if (path != NULL)
		mini->cmd->path = get_executable_path(*mini->cmd, pwd, path);
	if (!mini->cmd->path)
		exit(127);
	execve(mini->cmd->path, mini->cmd->args, mini->cmd->args);
	perror(mini->cmd->path);
	exit(127);
}
