/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_executor.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrottger <wrottger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 17:10:42 by wrottger          #+#    #+#             */
/*   Updated: 2023/10/20 17:36:58 by wrottger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_builtin(t_minishell *mini)
{
	char	*name;

	name = mini->cmd->name;
	if (ft_strcmp(name, "env") == 0)
		return (ft_env(mini));
	if (ft_strcmp(name, "echo") == 0)
		return (ft_echo(mini->cmd));
	if (ft_strcmp(name, "cd") == 0)
		return (ft_cd(mini, mini->cmd));
	if (ft_strcmp(name, "pwd") == 0)
		return (ft_pwd());
	if (ft_strcmp(name, "export") == 0)
		return (ft_export(mini, mini->cmd));
	if (ft_strcmp(name, "unset") == 0)
		return (ft_unset(mini, mini->cmd));
	if (ft_strcmp(name, "exit") == 0)
		return (ft_exit(mini, mini->cmd));
	return (0);
}

int	is_builtin(char *name)
{
	if (!name)
		return (0);
	if (ft_strcmp(name, "env") == 0)
		return (1);
	if (ft_strcmp(name, "echo") == 0)
		return (1);
	if (ft_strcmp(name, "cd") == 0)
		return (1);
	if (ft_strcmp(name, "pwd") == 0)
		return (1);
	if (ft_strcmp(name, "export") == 0)
		return (1);
	if (ft_strcmp(name, "unset") == 0)
		return (1);
	if (ft_strcmp(name, "exit") == 0)
		return (1);
	return (0);
}

static void	dup2_exit(int new, int old)
{
	if (dup2(new, old) < 0)
		exit(EXIT_FAILURE);
}

static int	loop_files_builtin(
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
			return (-1);
		current_file = current_file->next;
	}
	return (1);
}

int	execute_single_builtin(t_minishell *mini)
{
	int	status;
	int	in_fds;
	int	out_fds;

	save_stdio(mini->std_io);
	in_fds = 0;
	out_fds = 1;
	loop_files_builtin(mini->cmd->files, &in_fds, &out_fds);
	dup2_exit(out_fds, 1);
	dup2_exit(in_fds, 0);
	status = execute_builtin(mini);
	load_stdio(mini->std_io);
	return (status);
}
