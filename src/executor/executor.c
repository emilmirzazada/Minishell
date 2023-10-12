/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrottger <wrottger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 14:44:09 by wrottger          #+#    #+#             */
/*   Updated: 2023/10/11 21:16:01 by wrottger         ###   ########.fr       */
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
	printf("COMMAND COUNT = %d", cmd_count);
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

static int	execute_command(t_minishell *mini)
{
	if (is_builtin(mini->cmd->cmd))
		return (execute_builtin(mini));
	else
		return (execute_program(mini));
}

int	execute_commands(t_minishell *mini)
{
	int		command_count;
	int		status;
	int		pid;
	int		*pipe_fds;
	int		j;

	printf("EXECUTING COMMAND\n");
	command_count = count_commands(mini);
	printf("COUNTED COMMANDS\n");
	if (command_count == 1 && is_builtin(mini->cmd->cmd))
	{
		printf("IS BUILTIN\n");
		save_stdio(mini->std_io);
		status = execute_builtin(mini);
		load_stdio(mini->std_io);
		return (status);
	}
	printf("CREATING PIPES\n");
	pipe_fds = create_pipes(command_count);
	printf("CREATED PIPES\n");
	j = 0;
	while (mini->cmd)
	{
		// save_stdio(mini->std_io);
		// configure_pipes(mini, pipe_fds, j);
		printf("MAKING FORKS\n");
		pid = fork();
		if (pid == 0)
		{
			// if (mini->cmd->next)
			// 	if (dup2(pipe_fds[j + 1], 1) < 0)
			// 		exit(EXIT_FAILURE);
			// if (j != 0)
			// 	if (dup2(pipe_fds[j - 2], 0) < 0)
			// 		exit(EXIT_FAILURE);
			configure_pipes(mini, pipe_fds, j);
			if (clean_pipes(pipe_fds, command_count * 2) == -1)
				exit(EXIT_FAILURE);
			execute_command(mini);
		}
		else if (pid < 0)
			exit(EXIT_FAILURE);
		// load_stdio(mini->std_io);
		mini->cmd = mini->cmd->next;
		j += 2;
	}
	printf("Finished Execution\n");
	clean_pipes(pipe_fds, command_count * 2);
	j = 0;
	while (j++ < command_count + 1)
		wait(&status);
	return (getexitstatus(status));
}
