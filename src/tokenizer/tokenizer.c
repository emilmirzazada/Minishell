/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emirzaza <emirzaza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 23:29:26 by emirzaza          #+#    #+#             */
/*   Updated: 2023/11/02 17:05:33 by emirzaza         ###   ########.fr       */
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
bool	check_redirect_err(char *word)
{
	int	i;
	int	char_count;

	i = 0;
	while (word[i + 1])
	{
		if (word[0] != '"' && word[i] == '>' && word[i + 1] == '<')
			return (false);
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
		return (false);
	return (true);
}

bool	create_arg_token(t_split *split)
{
	if (split->is_text == false)
	{
		if (check_redirect_err(split->arg) == false)
		{
			ft_putstr_fd("Minishell: unexpected token\n", 2);
			return (false);
		}
	}
	return (true);
}

bool	create_lex(t_minishell *mini, t_split *split)
{
	t_lex		*new_lex;

	new_lex = (t_lex *)ft_calloc(sizeof(t_lex), 1);
	if (!(ft_strncmp(split->arg, "|", ft_strlen(split->arg))))
		new_lex->token = TOK_PIPE;
	else if (!(ft_strncmp(split->arg, "<", ft_strlen(split->arg))))
		new_lex->token = TOK_IN;
	else if (!(ft_strncmp(split->arg, ">", ft_strlen(split->arg))))
		new_lex->token = TOK_OUT;
	else if (!(ft_strncmp(split->arg, "<<", ft_strlen(split->arg))))
		new_lex->token = TOK_HERE_DOC;
	else if (!(ft_strncmp(split->arg, ">>", ft_strlen(split->arg))))
		new_lex->token = TOK_APPEND;
	else
	{
		if (!create_arg_token(split))
			return (false);
		new_lex->token = TOK_ARG;
	}
	new_lex->value = ft_strdup(split->arg);
	new_lex->next = NULL;
	ft_lex_addback(&(mini->lex), new_lex);
	return (true);
}

int	ft_lookup_input(t_minishell *mini)
{
	char	*expanded;
	t_split	*split;
	t_split	*start;

	expanded = expand(mini, false);
	if (ft_input_split(mini, expanded) == false)
		return (1);
	split = mini->split;
	start = split;
	while (split)
	{
		if (create_lex(mini, split))
			split = split->next;
		else
			return (1);
	}
	mini->split = start;
	if (parse_tokens(mini))
		return (mini->exit_code = 258, 1);
	return (0);
}
