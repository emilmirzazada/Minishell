/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emirzaza <emirzaza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 14:44:09 by wrottger          #+#    #+#             */
/*   Updated: 2023/10/18 21:31:45 by emirzaza         ###   ########.fr       */
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
	if (is_builtin(mini->cmd->name))
		return (execute_builtin(mini));
	else
		return (execute_program(mini));
}

static void	free_command(t_cmd *cmd)
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
	t_cmd	*tmp;
	int		status;
	int		pid;
	int		*pipe_fds;
	int		j;

	command_count = count_commands(mini);
	if (command_count == 1 && is_builtin(mini->cmd->name))
	{
		printf("IS BUILTIN\n");
		save_stdio(mini->std_io);
		status = execute_builtin(mini);
		load_stdio(mini->std_io);
		return (status);
	}
	pipe_fds = create_pipes(command_count);
	if (pipe_fds == NULL)
		perror_exit("Couldn't create pipes", mini, EXIT_FAILURE);
	printf("CREATED PIPES\n");
	j = 0;
	while (mini->cmd)
	{
		printf("MAKING FORKS\n");
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
	if (clean_pipes(pipe_fds, command_count * 2) == -1)
		perror_exit("Couldn't close pipes", mini, EXIT_FAILURE);
	j = 0;
	while (j++ < command_count + 1)
		wait(&status);
	printf("Finished Execution\n");
	return (getexitstatus(status));
}
