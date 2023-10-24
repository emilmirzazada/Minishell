/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emirzaza <emirzaza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 10:04:24 by emirzaza          #+#    #+#             */
/*   Updated: 2023/10/22 21:49:27 by emirzaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*split_quotes(char *s, int *i, char q)
{
	size_t		len;

	len = 1;
	while (len < ft_strlen(s) && s[len] != q)
		len++;
	len++;
	*i += len;
	return (ft_substr(s, 1, len - 2));
}

bool	ft_isspace(int c)
{
	return (c == ' ' || c == '\n' || c == '\r'
		|| c == '\v' || c == '\f' || c == '\t');
}

int	skip_spaces(char *s)
{
	int	i;

	i = 0;
	while (s[i] == ' ')
		i++;
	return (i);
}

int	skip_quotes(char *s, int i)
{
	char	quote;

	if (s[i] == '\'' || s[i] == '\"')
	{
		quote = s[i++];
		while (s[i] && s[i] != quote)
			i++;
	}
	return (i);
}

int	check_quotes(char *s)
{
	bool	double_quote;
	bool	single_quote;
	int		i;

	i = -1;
	double_quote = 0;
	single_quote = 0;
	while (s[++i] != '\0')
	{
		if (s[i] == '\'' && !double_quote && !single_quote)
			single_quote = 1;
		else if (s[i] == '\'' && !double_quote && single_quote)
			single_quote = false;
		else if (s[i] == '"' && !double_quote && !single_quote)
			double_quote = 1;
		else if (s[i] == '"' && double_quote && !single_quote)
			double_quote = false;
	}
	if (double_quote)
		return (-1);
	if (single_quote)
		return (-1);
	return (0);
}
