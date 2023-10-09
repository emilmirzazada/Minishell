/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrottger <wrottger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 14:44:09 by wrottger          #+#    #+#             */
/*   Updated: 2023/10/09 12:07:22 by wrottger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

static int	count_commands(t_minishell *mini)
{
	t_cmd	*tmp;
	int		cmd_count;

	tmp = mini->cmd;
	cmd_count = 0;
	while (tmp)
	{
		cmd_count++;
		tmp = tmp->next;
	}
	return (cmd_count);
}

static int	getexitstatus(int waitstatus)
{
	int	exitstatus;

	if (WIFEXITED(waitstatus))
		exitstatus = WEXITSTATUS(waitstatus);
	else
		exitstatus =  128 + WTERMSIG(waitstatus);
	return (exitstatus);
}

static int	execute_command(t_minishell *mini)
{
	char	*pwd;
	char	*path;

	if (is_builtin(mini->cmd->cmd))
		execute_builtin(mini);
	else
	{
		pwd = find_env(mini->env, "PWD");
		path = find_env(mini->env, "PATH");
		mini->cmd->path = get_executable_path(*mini->cmd, pwd, path);
		execve(mini->cmd->path, mini->cmd->args, mini->cmd->args);
	}
}

int	execute_commands(t_minishell *mini)
{
	int		command_count;
	int		status;
	int		pid;
	int		*pipe_fds;
	int		j;

	command_count = count_commands(mini);
	if (command_count == 1 && is_builtin(mini->cmd->cmd))
	{
		save_stdio(mini->std_io);
		status = execute_command(mini);
		load_stdio(mini->std_io);
		return (status);
	}
	pipe_fds = create_pipes(command_count);
	j = 0;
	save_stdio(mini->std_io);
	while (mini->cmd)
	{
		configure_pipes(mini, pipe_fds, j);
		pid = fork();
		if (pid == 0)
		{
			if (clean_pipes(pipe_fds, command_count * 2) == -1)
				exit(EXIT_FAILURE);
			execute_program(mini);
		}
		else if (pid < 0)
			exit(EXIT_FAILURE);
		mini->cmd = mini->cmd->next;
		j += 2;
	}
	clean_pipes(pipe_fds, command_count * 2);
	j = 0;
	while (j++ < command_count + 1)
		wait(&status);
	return (getexitstatus(status));
}
