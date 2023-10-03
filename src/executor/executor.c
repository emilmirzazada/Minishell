/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 18:13:05 by marvin            #+#    #+#             */
/*   Updated: 2023/10/03 18:16:23 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_commands(t_minishell *mini)
{
	t_cmd	*tmp;
	int	 cmd_count;

	tmp = mini->cmd;
	cmd_count = 0;
	while (tmp)
	{
		cmd_count++;
		tmp = tmp->next;
	}
	return (cmd_count);
}


static	int	child_execution(t_minishell *mini, int command_count, int *pipe_fds, int j)
{
	if(mini->cmd->next)
		if(dup2(pipe_fds[j + 1], 1) < 0)
			exit(EXIT_FAILURE);
	if(j != 0 )
		if(dup2(pipe_fds[j-2], 0) < 0)
			exit(EXIT_FAILURE);
	if (clean_pipes(pipe_fds, command_count * 2) == -1)
		exit(EXIT_FAILURE);
	if( execvp(*mini->cmd->args, mini->cmd->args) < 0 )
	{
		perror(*mini->cmd->args);
		exit(EXIT_FAILURE);
	}
	return (0);
}


int	execute_commands(t_minishell *mini)
{
	int		command_count;
	int		status;
	pid_t	pid;
	int		*pipe_fds;
	int		j;

	command_count = count_commands(mini);
	pipe_fds = create_pipes(command_count);
	j = 0;
	while(mini->cmd)
	{
		pid = fork();
		if(pid == 0)
			child_execution(mini, command_count, pipe_fds, j);
		else if(pid < 0)
			exit(EXIT_FAILURE);
		mini->cmd = mini->cmd->next;
		j+=2;
	}
	clean_pipes(pipe_fds, command_count * 2);
	j = 0;
	while (j < command_count + 1)
	{
		wait(&status);
		j++;
	}
	return (WEXITSTATUS(status));
}
