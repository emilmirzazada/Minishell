/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrottger <wrottger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 17:31:35 by wrottger          #+#    #+#             */
/*   Updated: 2023/10/16 16:49:16 by wrottger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	here_doc(char *delimiter)
{
	int		fd;
	int		line_len;
	char	*line;
	char	*old_line;
	char	*temp;

	fd = open("/tmp/minishell_heredoc", O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd == -1)
		exit(-500);
	line = NULL;
	while (true)
	{
		line_len = ft_strlen(line);
		temp = readline("heredoc>");
		if (line_len == 0)
			line = ft_strdup(temp);
		else if (line_len > 0)
		{
			old_line = line;
			line = ft_strjoin(line, temp);
			free(old_line);
		}
		free(temp);
		if (ft_strcmp(line + line_len, delimiter) == 0)
			break ;
	}
	return (fd);
}
