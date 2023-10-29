/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emirzaza <emirzaza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 11:56:50 by emirzaza          #+#    #+#             */
/*   Updated: 2023/10/29 17:18:36 by emirzaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//splits pipe and skips spaces
char	*split_pipe(char *s, int *i, char c)
{
	char	*arg;

	arg = NULL;
	if (c == ' ')
		*i += skip_spaces(s);
	else
	{
		*i = *i + 1;
		arg = ft_strdup("|");
	}
	return (arg);
}

int	check_ending(char *s, char *check)
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

char	*split_word(char *s, int *i)
{
	char	*arg;
	int		len;

	len = check_ending(&s[*i], " '\"|");
	arg = ft_substr(s, *i, len);
	*i += len;
	return (arg);
}

void	ft_split_addback(t_split **lst, t_split *new)
{
	t_split	**ptr;

	ptr = lst;
	while (*ptr)
		ptr = &(*ptr)->next;
	*ptr = new;
}

void	remove_split(t_split **head, char *key)
{
	t_split	**current;
	t_split	*temp;

	current = head;
	while (*current != NULL)
	{
		if (ft_strncmp((*current)->arg, key, ft_strlen(key) + 1) == 0)
		{
			temp = *current;
			*current = (*current)->next;
			free(temp->arg);
			free(temp);
			return ;
		}
		current = &(*current)->next;
	}
}
