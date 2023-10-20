/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrottger <wrottger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 09:39:25 by wrottger          #+#    #+#             */
/*   Updated: 2023/10/20 16:14:31 by wrottger         ###   ########.fr       */
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

static int	loop_files(
			t_minishell *mini,
			t_file *current_file,
			int *in_fds,
			int *out_fds)
{
	while (current_file)
	{
		if (current_file->token == TOK_IN
			|| current_file->token == TOK_HERE_DOC)
			close(*in_fds);
		if (current_file->token == TOK_IN)
			*in_fds = open(current_file->name, O_RDONLY);
		if (current_file->token == TOK_HERE_DOC)
			*in_fds = current_file->fds;
		if (current_file->token == TOK_OUT
			|| current_file->token == TOK_APPEND)
			close(*out_fds);
		if (current_file->token == TOK_OUT)
			*out_fds = open(current_file->name,
					O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (current_file->token == TOK_APPEND)
			*out_fds = open(current_file->name,
					O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (*in_fds == -1 || *out_fds == -1)
			perror_exit(current_file->name, mini, 1);
		current_file = current_file->next;
	}
	return (1);
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
	if (loop_files(mini, current_file, &in_fds, &out_fds) == -1)
		return (-1);
	if (out_fds != 1)
		dup2_exit(out_fds, 1);
	else if (mini->cmd->next)
		dup2_exit(pipe_fds[j + 1], out_fds);
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
