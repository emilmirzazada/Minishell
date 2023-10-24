/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrottger <wrottger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 17:31:35 by wrottger          #+#    #+#             */
/*   Updated: 2023/10/22 13:44:55 by wrottger         ###   ########.fr       */
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

int	here_doc(char *delimiter, char *name)
{
	int		fd;

	fd = open(name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		exit(-500);
	get_all_lines(delimiter, fd);
	fd = open(name, O_RDONLY);
	if (fd == -1)
		exit(-500);
	return (fd);
}

void	create_heredocs(t_minishell *mini)
{
	t_cmd	*tmp_cmd;
	t_file	*tmp_file;
	int		cmd_count;
	char	*cmd_count_str;
	char	*f_name;

	tmp_cmd = mini->cmd;
	cmd_count = -1;
	while (tmp_cmd)
	{
		tmp_file = tmp_cmd->files;
		while (tmp_file)
		{
			if (tmp_file->token == TOK_HERE_DOC)
			{
				cmd_count_str = ft_itoa(++cmd_count);
				f_name = ft_strjoin("/tmp/minishell_heredoc", cmd_count_str);
				free(cmd_count_str);
				tmp_file->fds = here_doc(tmp_file->delimeter,
						f_name);
			}
			tmp_file = tmp_file->next;
		}
		tmp_cmd = tmp_cmd->next;
	}
}
