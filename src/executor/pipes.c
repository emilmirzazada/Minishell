/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrottger <wrottger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 09:39:25 by wrottger          #+#    #+#             */
/*   Updated: 2023/10/05 09:40:40 by wrottger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	*create_pipes(int pipe_count)
{
	int	*pipe_fds;
	int	i;

	pipe_fds = (int *) ft_calloc(2 * pipe_count + 1, sizeof(pipe_fds));
	i = 0;
	while (i < pipe_count)
	{
		if (pipe(pipe_fds + i * 2) < 0)
		{
			perror("couldn't pipe");
			exit(EXIT_FAILURE);
		}
		i++;
	}
	return (pipe_fds);
}

int	clean_pipes(int *pipes, int size)
{
	int	i;
	int	return_value;

	i = 0;
	while (i < size)
	{
		return_value = close(pipes[i]);
		if (return_value == -1)
			return (-1);
		i++;
	}
	return (0);
}
