/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emirzaza <emirzaza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 17:40:07 by emirzaza          #+#    #+#             */
/*   Updated: 2023/10/16 15:25:45 by emirzaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*substring_argument(char *s, char *start, bool is_first)
{
	char	*temp;
	char	*res;
	
	res = NULL;
	temp = ft_substr(start, 0, s - start);
	if (ft_strcmp(temp, "'") && ft_strcmp(temp, "\""))
	{
		if (is_first == 1)
			res = ft_removechr(temp, '\\');
		else
			res = temp;
	}
	else
	{
		res = ft_strdup(" ");
		free(temp);
	}
	return (res);
}

bool	iterate_string(char **s, bool *is_end)
{
	if (**s)
		++(*s);
	else
	{
		*is_end = true;
		return (false);
	}
	return (true);
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
