/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir_tokens.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emirzaza <emirzaza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 15:06:01 by emirzaza          #+#    #+#             */
/*   Updated: 2023/09/12 14:20:06 by emirzaza         ###   ########.fr       */
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

void	create_file(t_minishell *mini, t_token token, char *name)
{
	t_file		*new_file;

	new_file = (t_file *)malloc(sizeof(t_file));
	new_file->token = token;
	new_file->name = ft_strdup(name);
	new_file->next = NULL;
	ft_file_addback(&(mini->file), new_file);
}

int	handle_redir_tokens(t_minishell *mini, t_lex **lex)
{
	t_token	token;

	token = (*lex)->token;
	if (!((*lex)->next))
	{
		ft_putstr_fd("Minishell: Unexpected token", 2);
		return (1);
	}
	create_file(mini, token, (*lex)->next->value);
	*lex = (*lex)->next;
	return (0);
}
