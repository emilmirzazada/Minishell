/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emirzaza <emirzaza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 23:29:26 by emirzaza          #+#    #+#             */
/*   Updated: 2023/09/10 23:54:43 by emirzaza         ###   ########.fr       */
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

void	create_lex(t_minishell *mini, char *split, int *pos)
{
	t_lex		*new_lex;

	new_lex = (t_lex *)malloc(sizeof(t_lex));
	(*pos)++;
	if (!(ft_strncmp(split, "|", ft_strlen(split))))
	{
		new_lex->token = TOK_PIPE;
		*pos = 0;
	}
	else if (!(ft_strncmp(split, "<", ft_strlen(split))))
		new_lex->token = TOK_IN;
	else if (!(ft_strncmp(split, ">", ft_strlen(split))))
		new_lex->token = TOK_OUT;
	else
		new_lex->token = TOK_WORD;
	new_lex->value = ft_strdup(split);
	new_lex->pos = *pos;
	new_lex->next = NULL;
	ft_lex_addback(&(mini->lex), new_lex);
}

void	ft_lookup_input(t_minishell *mini, char *input)
{
	char	**split;
	int		pos;

	pos = 0;
	split = ft_split(input,  ' ');
	while (*split)
	{
		create_lex(mini, *split, &pos);
		split++;
	}
}

void	parse_tokens(t_minishell *mini)
{
	t_lex	*temp;

	temp = mini->lex;
	while (temp)
	{
		ft_putstr_fd(temp->value, 2);
		ft_putstr_fd("\n", 2);
		temp = temp->next;
		//TODO: EM: CREATE COMMANDS HERE
	}
}