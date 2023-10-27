/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrottger <wrottger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 14:44:09 by wrottger          #+#    #+#             */
/*   Updated: 2023/10/27 14:30:12 by wrottger         ###   ########.fr       */
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
		exitstatus = 128 + WTERMSIG(waitstatus);
	return (exitstatus);
}

int	execute_command(t_minishell *mini)
{
	if (is_builtin(mini->cmd->name))
		exit(execute_builtin(mini));
	else
		return (execute_program(mini));
}

void	free_command(t_cmd *cmd)
{
	int		i;
	t_file	*tmp;

	i = 0;
	while (cmd->args[i])
		free(cmd->args[i++]);
	tmp = cmd->files;
	while (tmp)
	{
		if (tmp->delimeter)
			free(tmp->delimeter);
		if (tmp->name)
			free(tmp->name);
		tmp = tmp->next;
	}
	free(cmd->path);
	free(cmd->args);
	free(cmd);
	cmd = NULL;
}

int	execute_commands(t_minishell *mini)
{
	int		command_count;
	int		status;
	int		*pipe_fds;
	int		i;

	if (mini->cmd == NULL)
		return (0);
	command_count = count_commands(mini);
	if (mini->cmd)
		create_heredocs(mini);
	if (command_count == 1 && is_builtin(mini->cmd->name))
		return (execute_single_builtin(mini));
	mini->pids = (int *) ft_calloc(command_count, sizeof(mini->pids));
	pipe_fds = create_pipes(command_count);
	if (pipe_fds == NULL)
		perror_exit("Couldn't create pipes", mini, EXIT_FAILURE);
	loop_commands(mini, pipe_fds, command_count);
	if (clean_pipes(pipe_fds, command_count * 2) == -1)
		perror_exit("Couldn't close pipes", mini, EXIT_FAILURE);
	i = 0;
	while (i++ < command_count)
		waitpid(mini->pids[i - 1], &status, 0);
	free(mini->pids);
	mini->pids = NULL;
	return (getexitstatus(status));
}
