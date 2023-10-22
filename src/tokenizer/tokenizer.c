/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emirzaza <emirzaza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 23:29:26 by emirzaza          #+#    #+#             */
/*   Updated: 2023/10/15 16:56:44 by emirzaza         ###   ########.fr       */
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

//max length for redirect tokens is 2, more than that is syntax error
int	check_redirect_err(char *word)
{
	int	i;
	int	char_count;

	i = 0;
	while (word[i + 1])
	{
		if (word[0] != '"' && word[i] == '>' && word[i + 1] == '<')
			return (1);
		i++;
	}
	i = -1;
	char_count = 0;
	if (word[0] == '\'' || word[0] == '"')
		return (0);
	while (word[++i])
	{
		if (word[i] == '<' || word[i] == '>')
			char_count++;
	}
	if (char_count > 2)
		return (1);
	return (0);
}

int	create_arg_token(char *split)
{
	if (check_redirect_err(split))
	{
		ft_putstr_fd("Minishell: unexpected token\n", 2);
		return (1);
	}
	return (0);
}

bool	create_lex(t_minishell *mini, char **split)
{
	t_lex		*new_lex;

	new_lex = (t_lex *)malloc(sizeof(t_lex));
	if (!(ft_strncmp(*split, "|", ft_strlen(*split))))
		new_lex->token = TOK_PIPE;
	else if (!(ft_strncmp(*split, "<", ft_strlen(*split))))
		new_lex->token = TOK_IN;
	else if (!(ft_strncmp(*split, ">", ft_strlen(*split))))
		new_lex->token = TOK_OUT;
	else if (!(ft_strncmp(*split, "<<", ft_strlen(*split))))
		new_lex->token = TOK_HERE_DOC;
	else if (!(ft_strncmp(*split, ">>", ft_strlen(*split))))
		new_lex->token = TOK_APPEND;
	else
	{
		if (create_arg_token(*split))
			return (false);
		new_lex->token = TOK_ARG;
	}
	new_lex->value = ft_strdup(*split);
	new_lex->next = NULL;
	ft_lex_addback(&(mini->lex), new_lex);
	return (true);
}

int	ft_lookup_input(t_minishell *mini, char *input)
{
	char	*expanded;
	char	**split;

	expanded = expand(mini, input);
	split = ft_input_split(expanded);
	if (!split)
		return (1);
	while (*split)
	{
		if (create_lex(mini, split))
			split++;
		else
			return (1);
	}
	if (parse_tokens(mini))
		return (1);
	return (0);
}
