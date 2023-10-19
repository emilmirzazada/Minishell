/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrottger <wrottger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 14:44:09 by wrottger          #+#    #+#             */
/*   Updated: 2023/10/19 19:57:23 by wrottger         ###   ########.fr       */
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
	int	i;

	i = 0;
	while (cmd->args[i])
		free(cmd->args[i++]);
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

	command_count = count_commands(mini);
	pipe_fds = create_pipes(command_count);
	if (mini->cmd)
		create_heredocs(mini);
	if (pipe_fds == NULL)
		perror_exit("Couldn't create pipes", mini, EXIT_FAILURE);
	if (command_count == 1 && is_builtin(mini->cmd->name))
		return (execute_single_builtin(mini, pipe_fds, command_count));
	loop_commands(mini, pipe_fds, command_count);
	if (clean_pipes(pipe_fds, command_count * 2) == -1)
		perror_exit("Couldn't close pipes", mini, EXIT_FAILURE);
	i = 0;
	while (i++ < command_count + 1)
		wait(&status);
	return (getexitstatus(status));
}
