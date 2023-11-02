/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrottger <wrottger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 17:31:35 by wrottger          #+#    #+#             */
/*   Updated: 2023/11/02 10:37:44 by wrottger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	get_all_lines(t_minishell *mini, char *delimiter, char *name)
{
	char	*temp;
	int		fd;

	free(mini->input);
	mini->input = NULL;
	while (true)
	{
		temp = readline("heredoc>");
		if (!temp || ft_strcmp(temp, delimiter) == 0)
			return ;
		mini->input = temp;
		temp = expand(mini);
		fd = open(name, O_WRONLY | O_APPEND | O_CREAT, 0644);
		if (fd == -1)
			perror_exit(name, mini, -1);
		write(fd, temp, ft_strlen(temp));
		write(fd, "\n", 1);
		close(fd);
		free(temp);
		temp = NULL;
	}
	free(temp);
}

int	here_doc(t_minishell *mini, char *delimiter, char *name)
{
	get_all_lines(mini, delimiter, name);
	return (1);
}

void	create_heredocs(t_minishell *mini)
{
	t_cmd	*tmp_cmd;
	t_file	*tmp_file;
	int		cmd_count;
	char	*cmd_count_str;

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
				tmp_file->name = ft_strjoin(HEREDOC_DIR, cmd_count_str);
				free(cmd_count_str);
				here_doc(mini, tmp_file->delimeter, tmp_file->name);
			}
			tmp_file = tmp_file->next;
		}
		tmp_cmd = tmp_cmd->next;
	}
}
