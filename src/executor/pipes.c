/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrottger <wrottger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 09:39:25 by wrottger          #+#    #+#             */
/*   Updated: 2023/10/19 17:29:30 by wrottger         ###   ########.fr       */
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

static int	loop_files(t_file *current_file, int *in_fds, int *out_fds)
{
	while (current_file)
	{
		if (current_file->token == TOK_IN)
		{
			if (*in_fds != 0)
				close(*in_fds);
			*in_fds = open(current_file->name, O_RDONLY);
			if (*in_fds == -1)
			{
				perror(current_file->name);
				exit(EXIT_FAILURE);
			}
		}
		if (current_file->token == TOK_HERE_DOC)
		{
			if (*in_fds != 0)
				close(*in_fds);
			*in_fds = current_file->fds;
		}
		if (current_file->token == TOK_OUT)
		{
			if (*out_fds != 1)
				close(*out_fds);
			*out_fds = open(current_file->name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		}
		if (current_file->token == TOK_APPEND)
		{
			if (*out_fds != 1)
				close(*out_fds);
			*out_fds = open(current_file->name, O_CREAT | O_WRONLY | O_APPEND, 0644);
		}
		current_file = current_file->next;
		if (*in_fds == -1 || *out_fds == -1)
			return (-1);
	}
	return (1);
}

int	configure_pipes(t_minishell *mini, int *pipe_fds, int j)
{
	t_file	*current_file;
	int		in_fds;
	int		out_fds;

	current_file = mini->cmd->files;
	in_fds = 0;
	out_fds = 1;
	if (loop_files(current_file, &in_fds, &out_fds) == -1)
		return (-1);
	if (out_fds != 1)
	{
		if (dup2(out_fds, 1) < 0)
			exit(EXIT_FAILURE);
	}
	else if (mini->cmd->next)
		if (dup2(pipe_fds[j + 1], out_fds) < 0)
			exit(EXIT_FAILURE);

	if (in_fds != 0)
	{
		if (dup2(in_fds, 0) < 0)
			exit(EXIT_FAILURE);
	}
	else if (j != 0)
		if (dup2(pipe_fds[j - 2], in_fds) < 0)
			exit(EXIT_FAILURE);
	return (1);
}

int	clean_pipes(int *pipes, int size)
{
	int	i;
	int	return_value;

	i = 0;
	while (i < size)
	{
		return_value = close(pipes[i]);
		i++;
	}
	return (0);
}
