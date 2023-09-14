/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emirzaza <emirzaza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 23:29:26 by emirzaza          #+#    #+#             */
/*   Updated: 2023/09/12 14:32:57 by emirzaza         ###   ########.fr       */
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

void	create_lex(t_minishell *mini, char *split)
{
	t_lex		*new_lex;

	new_lex = (t_lex *)malloc(sizeof(t_lex));
	if (!(ft_strncmp(split, "|", ft_strlen(split))))
	{
		new_lex->token = TOK_PIPE;
	}
	else if (!(ft_strncmp(split, "<", ft_strlen(split))))
		new_lex->token = TOK_IN;
	else if (!(ft_strncmp(split, ">", ft_strlen(split))))
		new_lex->token = TOK_OUT;
	else
		new_lex->token = TOK_WORD;
	new_lex->value = ft_strdup(split);
	new_lex->next = NULL;
	ft_lex_addback(&(mini->lex), new_lex);
}

void	ft_lookup_input(t_minishell *mini, char *input)
{
	char	**split;

	split = ft_input_split(input);
	while (*split)
	{
		create_lex(mini, *split);
		split++;
	}
	parse_tokens(mini);
}
