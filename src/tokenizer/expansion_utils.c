/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emirzaza <emirzaza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 19:34:47 by emirzaza          #+#    #+#             */
/*   Updated: 2023/10/27 13:58:12 by emirzaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expansion_end_check(char *s, char *check)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		j = 0;
		while (check[j] != '\0')
		{
			if (s[i] == check[j])
				return (i);
			j++;
		}
		i++;
	}
	return (i);
}

char	*place_value(char *temp, char *value, char *s, int *t)
{
	char	*new_temp;

	if (value && value[0] != '\0')
	{
		*t += ft_strlen(value);
		new_temp = ft_strjoin(temp, value);
		if (!new_temp)
			return (new_temp);
		free(temp);
		temp = ft_calloc((ft_strlen(s) + ft_strlen(value) + 1), sizeof(char));
		if (!temp)
			return (NULL);
		ft_strlcpy(temp, new_temp, (ft_strlen(s)
				+ ft_strlen(value) + 1) * sizeof(char) + 1);
		free(value);
		free(new_temp);
	}
	return (temp);
}

void	copy_quotted_part(char *temp, char *s, int *i, int *t)
{
	while (s[*i] && s[*i] != '\'')
	{
		temp[*t] = s[*i];
		if (*t <= (int)ft_strlen(temp))
			(*t)++;
		(*i)++;
	}
}

// When encounters a single quote, copies all characters between the two 
// single quotes and continues copying characters one by one afterward.
void	place_rest_of_string(char *s, char *temp, int *i, int *t)
{
	int	slen;
	int	tlen;

	slen = ft_strlen(s);
	tlen = ft_strlen(temp);
	if (s[*i] && s[*i] == '\'')
	{
		temp[*t] = s[*i];
		(*t)++;
		(*i)++;
		copy_quotted_part(temp, s, i, t);
	}
	temp[*t] = s[*i];
	if (s[*i])
	{
		(*i)++;
		(*t)++;
	}
}

char	*get_name(char *s, int i)
{
	int		j;
	char	*name;

	j = 0;
	name = malloc((i + 2) * sizeof(char));
	if (!name)
		return (name);
	while (j < i - 1)
	{
		name[j] = s[j];
		j++;
	}
	name[j] = '\0';
	return (name);
}
