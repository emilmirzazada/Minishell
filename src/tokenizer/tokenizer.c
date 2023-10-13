/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emirzaza <emirzaza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 23:29:26 by emirzaza          #+#    #+#             */
/*   Updated: 2023/10/13 13:23:32 by emirzaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lex_addback(t_lex **lst, t_lex *new)
{
	t_lex	**ptr;

	ptr = lst;
	while (*ptr)
		ptr = &(*ptr)->next;
	*ptr = new;
}

int	create_lex(t_minishell *mini, char *split)
{
	t_lex		*new_lex;
	int			length;

	new_lex = (t_lex *)malloc(sizeof(t_lex));
	length = 1;
	if (!(ft_strncmp(split, "|", ft_strlen(split))))
	{
		new_lex->token = TOK_PIPE;
	}
	else if (!(ft_strncmp(split, "<<", ft_strlen(split))))
	{
		new_lex->token = TOK_HERE_DOC;
		length = 2;
	}
	else if (!(ft_strncmp(split, ">>", ft_strlen(split))))
	{
		new_lex->token = TOK_APPEND;
		length = 2;
	}
	else if (!(ft_strncmp(split, "<", ft_strlen(split))))
		new_lex->token = TOK_IN;
	else if (!(ft_strncmp(split, ">", ft_strlen(split))))
		new_lex->token = TOK_OUT;
	else
		new_lex->token = TOK_ARG;
	new_lex->value = ft_strdup(split);
	new_lex->next = NULL;
	ft_lex_addback(&(mini->lex), new_lex);
	return (length);
}

void	ft_lookup_input(t_minishell *mini, char *input)
{
	char	*expanded;
	char	**split;

	expanded = expand(mini, input);
	split = ft_input_split(input);
	while (*split)
	{
		split += create_lex(mini, *split);
	}
	parse_tokens(mini);
}
