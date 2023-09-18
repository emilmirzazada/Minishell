/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emirzaza <emirzaza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 13:12:41 by emirzaza          #+#    #+#             */
/*   Updated: 2023/09/12 14:19:34 by emirzaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_token_type(t_minishell *mini, t_lex **lex)
{
	if ((*lex)->token == TOK_IN || (*lex)->token == TOK_OUT)
	{
		if (handle_redir_tokens(mini, lex))
			return (1);
	}
	else if ((*lex)->token == TOK_WORD)
	{
		if (handle_word_tokens(mini, lex))
			return (1);
	}
	return (0);
}

int	parse_tokens(t_minishell *mini)
{
	t_lex	*temp;
	t_lex	*temp_prev;

	temp = mini->lex;
	temp_prev = mini->lex;
	while (temp)
	{
		if (temp_prev->token == TOK_OUT)
			break ;
		if (handle_token_type(mini, &temp))
			return (1);
		if (temp)
		{
			temp_prev = temp;
			temp = temp->next;
		}
	}
	return (0);
}
