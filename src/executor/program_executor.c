/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program_executor.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrottger <wrottger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 08:38:10 by wrottger          #+#    #+#             */
/*   Updated: 2023/10/19 19:15:46 by wrottger         ###   ########.fr       */
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
	if (!mini->cmd->name)
		exit(0);
	execve(mini->cmd->path, mini->cmd->args, mini->env_arr);
	perror_exit(mini->cmd->path, mini, 127);
	return (-1);
}

int	loop_commands(t_minishell *mini, int *pipe_fds, int command_count)
{
	int		j;
	int		pid;
	t_cmd	*tmp;

	j = 0;
	while (mini->cmd)
	{
		pid = fork();
		if (pid == 0)
		{
			configure_pipes(mini, pipe_fds, j);
			if (clean_pipes(pipe_fds, command_count * 2) == -1)
				perror_exit("Couldn't close pipes", mini, EXIT_FAILURE);
			init_non_interactive_signals();
			execute_command(mini);
		}
		else if (pid < 0)
			perror_exit("Couldn't fork", mini, EXIT_FAILURE);
		tmp = mini->cmd;
		mini->cmd = mini->cmd->next;
		free_command(tmp);
		j += 2;
	}
	return (0);
}
