/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_redirects.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emirzaza <emirzaza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 18:52:00 by emirzaza          #+#    #+#             */
/*   Updated: 2023/10/26 17:13:00 by emirzaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cnt_needed_sp(char *s)
{
	int	i;
	int	count;

	count = 0;
	i = -1;
	while (s[++i] != '\0')
	{
		if (s[i] == '<' || s[i] == '>')
		{
			if (s[i + 1] != ' ' && s[i + 1] != '\0')
				count++;
			if (i > 0 && s[i - 1] != ' ')
				count++;
		}
	}
	return (count);
}

char	*add_char_to_string(char *old_str, char c, int index)
{
	int		len;
	char	*new_str;

	len = ft_strlen(old_str);
	new_str = (char *)malloc(len + 2);
	if (new_str == NULL)
		return (NULL);
	ft_strncpy(new_str, old_str, index);
	new_str[index] = c;
	ft_strncpy(new_str + index + 1, old_str + index,
		ft_strlen(old_str + index));
	return (new_str);
}

char	*add_space_before_redir(char *old_str)
{
	int		i;
	char	*new_str;
	char	*temp;

	i = 0;
	new_str = ft_strdup(old_str);
	while (old_str[i] != '\0')
	{
		i = skip_quotes(old_str, i);
		if (old_str[i] == '<' || old_str[i] == '>')
		{
			if (i > 0 && old_str[i - 1] != ' ' && old_str[i - 1] != '<'
				&& old_str[i - 1] != '>')
			{
				temp = new_str;
				new_str = add_char_to_string(temp, ' ', i);
				old_str = new_str;
				free(temp);
			}
		}
		i++;
	}
	return (new_str);
}

char	*add_space_after_redir(char *old_str)
{
	int		i;
	char	*new_str;
	char	*temp;

	i = 0;
	new_str = ft_strdup(old_str);
	while (old_str[i] != '\0')
	{
		i = skip_quotes(old_str, i);
		if (old_str[i] == '<' || old_str[i] == '>')
		{
			if (old_str[i + 1] != ' ' && old_str[i + 1] != '<'
				&& old_str[i + 1] != '>')
			{
				temp = new_str;
				new_str = add_char_to_string(temp, ' ', i + 1);
				old_str = new_str;
				free(temp);
			}
		}
		i++;
	}
	return (new_str);
}

char	*handle_redir_symbols(char *s)
{
	s = add_space_before_redir(s);
	s = add_space_after_redir(s);
	return (s);
}
