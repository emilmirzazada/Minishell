/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program_executor.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrottger <wrottger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 08:38:10 by wrottger          #+#    #+#             */
/*   Updated: 2023/10/19 17:43:38 by wrottger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_directory(char *path)
{
	struct stat	path_stat;

	stat(path, &path_stat);
	return (S_ISDIR(path_stat.st_mode));
}

int	execute_program(t_minishell *mini)
{
	char	*path;

	path = find_env(mini->env, "PATH");
	if (is_directory(mini->cmd->name))
	{
		errno = EISDIR;
		perror_exit(mini->cmd->name, mini, 126);
	}
	if (path != NULL)
		mini->cmd->path = get_executable_path(*mini->cmd, path);
	if (!mini->cmd->path && mini->cmd->name)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(mini->cmd->name, 2);
		ft_putstr_fd(": command not found\n", 2);
		free_mini(mini);
		exit(127);
	}
	printf("PATH = %s", mini->cmd->path);
	if (!mini->cmd->name)
		exit(0);
	execve(mini->cmd->path, mini->cmd->args, mini->env_arr);
	perror_exit(mini->cmd->path, mini, 127);
	return (-1);
}
