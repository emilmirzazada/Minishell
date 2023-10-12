/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir_tokens.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emirzaza <emirzaza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 15:06:01 by emirzaza          #+#    #+#             */
/*   Updated: 2023/10/12 12:48:29 by emirzaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_file_addback(t_file **lst, t_file *new)
{
	t_file	**ptr;

	ptr = lst;
	while (*ptr)
		ptr = &(*ptr)->next;
	*ptr = new;
}

void	create_file(t_cmd *cmd, t_token token, char *name)
{
	t_file		*new_file;

	new_file = (t_file *)malloc(sizeof(t_file));
	new_file->delimeter = NULL;
	new_file->name = NULL;
	new_file->token = token;
	if (token == TOK_HERE_DOC)
		new_file->delimeter = ft_strdup(name);
	else
		new_file->name = ft_strdup(name);
	new_file->next = NULL;
	ft_file_addback(&cmd->files, new_file);
}

int	handle_redir_tokens(t_cmd *cmd, t_lex **lex)
{
	t_token	token;

	token = (*lex)->token;
	if (!((*lex)->next))
	{
		ft_putstr_fd("Minishell: Unexpected token", 2);
		return (1);
	}
	create_file(cmd, token, (*lex)->next->value);
	*lex = (*lex)->next;
	(*lex)->token = token;
	return (0);
}

int	handle_heredoc_token(t_cmd *cmd, t_lex **lex)
{
	t_token	token;

	token = (*lex)->token;
	if (!(*lex)->next)
	{
		ft_putstr_fd("Provide delimiter for heredoc\n", 2);
		return (1);
	}
	*lex = (*lex)->next;
	if ((*lex)->token != TOK_ARG)
	{
		ft_putstr_fd("Provide delimiter for heredoc\n", 2);
		return (1);
	}
	create_file(cmd, TOK_HERE_DOC, (*lex)->value);
	(*lex)->token = token;
	return (0);
}
