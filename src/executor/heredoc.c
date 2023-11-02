/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrottger <wrottger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 17:31:35 by wrottger          #+#    #+#             */
/*   Updated: 2023/11/02 16:42:59 by wrottger         ###   ########.fr       */
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
		temp = readline("> ");
		if (!temp || ft_strcmp(temp, delimiter) == 0)
			return ;
		mini->input = temp;
		temp = expand(mini);
		free(mini->input);
		mini->input = NULL;
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
	int			pid;
	int			status;

	init_non_interactive_signals();
	pid = fork();
	if (pid == -1)
		perror_exit("fork_failed", mini, -1);
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		free(mini->input);
		mini->input = NULL;
		get_all_lines(mini, delimiter, name);
		exit(0);
	}
	status = 0;
	waitpid(pid, &status, 0);
	if (WTERMSIG(status) == SIGINT)
	{
		write(1, "\n", 1);
		return (-1);
	}
	return (1);
}

int	create_heredocs(t_minishell *mini)
{
	t_file	*tmp_file;
	t_cmd	*tmp_cmd;
	char	*cmd_count_str;
	int		cmd_count;

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
				if (here_doc(mini, tmp_file->delimeter, tmp_file->name) == -1)
					return (-1);
			}
			tmp_file = tmp_file->next;
		}
		tmp_cmd = tmp_cmd->next;
	}
	return (1);
}
