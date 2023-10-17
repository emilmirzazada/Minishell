/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrottger <wrottger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 09:39:25 by wrottger          #+#    #+#             */
/*   Updated: 2023/10/17 13:13:28 by wrottger         ###   ########.fr       */
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
		printf("FILES = %s\n", current_file->name);
		printf("TOKEN = %u\n", current_file->token);
		printf("TOKEN OUT = %d\n", TOK_OUT);
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
			*in_fds = here_doc(current_file->delimeter);
			if (*in_fds == -1)
			{
				perror(current_file->name);
				exit(EXIT_FAILURE);
			}
		}
		if (current_file->token == TOK_OUT)
		{
			if (*out_fds != 1)
				close(*out_fds);
			*out_fds = open(current_file->name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
			printf("OUTFDS = %d\n", *out_fds);
		}
		if (current_file->token == TOK_APPEND)
		{
			if (*out_fds != 1)
				close(*out_fds);
			*out_fds = open(current_file->name, O_CREAT | O_WRONLY | O_APPEND, 0644);
			printf("OUTFDS = %d\n", *out_fds);
		}
		current_file = current_file->next;
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
	printf("SEARCHING FOR FILE\n");
	out_fds = 1;
	loop_files(current_file, &in_fds, &out_fds);
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
		printf("IN FDS = %d\n", in_fds);
		if (dup2(in_fds, 0) < 0)
			exit(EXIT_FAILURE);
	}
	else if (j != 0)
		if (dup2(pipe_fds[j - 2], in_fds) < 0)
			exit(EXIT_FAILURE);
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
