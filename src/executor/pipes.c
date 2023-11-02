/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrottger <wrottger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 09:39:25 by wrottger          #+#    #+#             */
/*   Updated: 2023/11/02 13:47:17 by wrottger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	*create_pipes(int pipe_count)
{
	int	*pipe_fds;
	int	i;

	pipe_fds = (int *) ft_calloc(2 * pipe_count + 1, sizeof(pipe_fds));
	if (!pipe_fds)
		return (NULL);
	i = 0;
	while (i < pipe_count)
	{
		if (pipe(pipe_fds + i * 2) < 0)
		{
			return (NULL);
		}
		i++;
	}
	return (pipe_fds);
}

static void	loop_files(
			t_minishell *mini,
			t_file *c_file,
			int *in_fds,
			int *out_fds)
{
	while (c_file)
	{
		if (c_file->token == TOK_IN || c_file->token == TOK_HERE_DOC)
		{
			if (*in_fds != 0)
				close(*in_fds);
			*in_fds = open(c_file->name, O_RDONLY);
		}
		if ((c_file->token == TOK_OUT || c_file->token == TOK_APPEND)
			&& *out_fds != 1)
			close(*out_fds);
		if (c_file->token == TOK_OUT)
			*out_fds = open(c_file->name,
					O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (c_file->token == TOK_APPEND)
			*out_fds = open(c_file->name,
					O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (*in_fds == -1 || *out_fds == -1)
		{
			clean_pipes(mini->pipes, mini->pipe_count * 2);
			perror_exit(c_file->name, mini, 1);
		}
		c_file = c_file->next;
	}
}

static void	dup2_exit(int new, int old)
{
	if (dup2(new, old) < 0)
		exit(EXIT_FAILURE);
}

int	configure_pipes(t_minishell *mini, int *pipe_fds, int j)
{
	t_file	*current_file;
	int		in_fds;
	int		out_fds;

	current_file = mini->cmd->files;
	in_fds = 0;
	out_fds = 1;
	loop_files(mini, current_file, &in_fds, &out_fds);
	if (out_fds != 1)
		dup2_exit(out_fds, 1);
	else if (mini->cmd->next)
		dup2_exit(pipe_fds[j + 1], out_fds);
	if (in_fds != 0)
		dup2_exit(in_fds, 0);
	else if (j != 0)
		dup2_exit(pipe_fds[j - 2], in_fds);
	if (in_fds != 0)
		close(in_fds);
	if (out_fds != 1)
		close(out_fds);
	return (1);
}

int	clean_pipes(int *pipes, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		close(pipes[i]);
		i++;
	}
	free(pipes);
	return (0);
}
