/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emirzaza <emirzaza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 13:12:41 by emirzaza          #+#    #+#             */
/*   Updated: 2023/10/12 13:20:21 by emirzaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_cmd_files(t_cmd *cmd, t_lex **temp)
{
	while ((*temp) && (*temp)->token != TOK_PIPE)
	{
		if ((*temp)->token == TOK_IN || (*temp)->token == TOK_OUT
			|| (*temp)->token == TOK_APPEND)
		{
			if (handle_redir_tokens(cmd, temp))
				return (1);
		}
		else if ((*temp)->token == TOK_HERE_DOC)
		{
			if (handle_heredoc_token(cmd, temp))
				return (1);
		}
		(*temp) = (*temp)->next;
	}
	return (0);
}

t_cmd	*finalize_cmd(t_minishell *mini, t_cmd *cmd, t_lex **lex, int *cmd_argc)
{
	if (*lex && ((*lex)->token == TOK_PIPE))
	{
		cmd->name = cmd->args[0];
		cmd->args[*cmd_argc] = 0;
		cmd = init_new_command(mini, *lex, cmd_argc);
	}
	if (*lex)
	{
		if (!((*lex)->next))
		{
			cmd->name = cmd->args[0];
			cmd->args[*cmd_argc] = 0;
			return (NULL);
		}
		else
			*lex = (*lex)->next;
	}
	else
	{
		cmd->name = cmd->args[0];
		cmd->args[*cmd_argc] = 0;
	}
	return (cmd);
}

void	parse_cmd_args(t_cmd *new_cmd, t_lex **lex, int *cmd_argc)
{
	while (*lex && (*lex)->token != TOK_PIPE && (*lex)->token == TOK_ARG)
	{
		new_cmd->args[(*cmd_argc)++] = ft_strdup((*lex)->value);
		if ((*lex)->next && (*lex)->next->token != TOK_OUT)
			*lex = (*lex)->next;
		else
			break ;
	}
}

int	parse_tokens(t_minishell *mini)
{
	int		cmd_argc;
	t_cmd	*new_cmd;
	t_lex	*iter1;
	t_lex	**iter2;

	iter1 = mini->lex;
	iter2 = &mini->lex;
	new_cmd = NULL;
	while (iter1)
	{
		if (new_cmd == NULL)
			new_cmd = init_new_command(mini, iter1, &cmd_argc);
		if (parse_cmd_files(new_cmd, iter2))
			return (1);
		parse_cmd_args(new_cmd, &iter1, &cmd_argc);
		if (iter1 && (iter1)->token == TOK_PIPE)
			*iter2 = iter1->next;
		new_cmd = finalize_cmd(mini, new_cmd, &iter1, &cmd_argc);
		if (new_cmd == NULL)
			return (0);
	}
	return (0);
}
