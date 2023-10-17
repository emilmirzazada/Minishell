/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrottger <wrottger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 17:31:35 by wrottger          #+#    #+#             */
/*   Updated: 2023/10/17 10:56:48 by wrottger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	get_all_lines(char *delimiter, int fd)
{
	char	*temp;

	while (true)
	{
		temp = readline("heredoc>");
		if (ft_strcmp(temp, delimiter) == 0)
			break ;
		write(fd, temp, ft_strlen(temp));
		write(fd, "\n", 1);
		free(temp);
	}
	free(temp);
}

int	here_doc(char *delimiter)
{
	int		fd;

	fd = open(HEREDOC_FILE, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		exit(-500);
	get_all_lines(delimiter, fd);
	fd = open(HEREDOC_FILE, O_RDONLY);
	if (fd == -1)
		exit(-500);
	return (fd);
}
