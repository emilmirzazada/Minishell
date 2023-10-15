/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program_executor.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emirzaza <emirzaza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 08:38:10 by wrottger          #+#    #+#             */
/*   Updated: 2023/10/15 16:48:54 by emirzaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_program(t_minishell *mini)
{
	char	*pwd;
	char	*path;

	pwd = getcwd(NULL, 0);
	path = find_env(mini->env, "PATH");
	if (path != NULL)
		mini->cmd->path = get_executable_path(*mini->cmd, pwd, path);
	if (!mini->cmd->path)
		exit(127);
	execve(mini->cmd->path, mini->cmd->args, mini->env_arr);
	perror(mini->cmd->path);
	exit(127);
}
