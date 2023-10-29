/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emirzaza <emirzaza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 19:34:47 by emirzaza          #+#    #+#             */
/*   Updated: 2023/10/29 23:28:28 by emirzaza         ###   ########.fr       */
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

char	*embrace_value(char *value)
{
	char	*formatted_value;
	char	*temp_val;

	formatted_value = ft_calloc(ft_strlen(value) + 3, sizeof(char));
	formatted_value[0] = '\"';
	ft_strlcat(formatted_value, value, ft_strlen(value) + 2);
	formatted_value[ft_strlen(value) + 1] = '\"';
	temp_val = value;
	value = formatted_value;
	free(temp_val);
	return (value);
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
	if (s[*i] && s[*i] == '\'')
	{
		temp[*t] = s[*i];
		(*t)++;
		(*i)++;
		copy_quotted_part(temp, s, i, t);
	}
	if (*t <= (int)ft_strlen(temp))
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
