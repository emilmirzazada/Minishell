/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_redirects.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emirzaza <emirzaza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 18:52:00 by emirzaza          #+#    #+#             */
/*   Updated: 2023/10/15 18:36:07 by emirzaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cnt_needed_sp(char *s)
{
	int		i;
	int		count;

	count = 0;
	i = -1;
	while (s[++i])
	{
		if (s[i] == '<' || s[i] == '>')
		{
			if (s[i + 1] != ' ')
				count++;
			if (i > 0 && s[i - 1] != ' ')
				count++;
		}
	}
	return (count);
}

char	*add_char_to_string(char *old_str, char *new_str, char c, int index)
{
	ft_memcpy(new_str, old_str, index);
	new_str[index] = c;
	ft_memcpy(new_str + index + 1, old_str + index,
		ft_strlen(new_str + index + 1));
	return (new_str);
}

char	*add_space_before_redir(char *old_str, char *new_str)
{
	int		i;
	char	*temp;

	i = -1;
	while (old_str[++i])
	{
		i = skip_quotes(old_str, i);
		if (old_str[i] == '<' || old_str[i] == '>')
		{
			if (i > 0 && old_str[i - 1] != ' ' && (old_str[i - 1] != '<'
					&& old_str[i - 1] != '>'))
			{
				temp = old_str;
				old_str = add_char_to_string(temp, new_str, ' ', i);
				free(temp);
				new_str = (char *)malloc((ft_strlen(old_str)
							+ cnt_needed_sp(old_str) + 2) * sizeof(char));
			}
		}
	}
	return (old_str);
}

char	*add_space_after_redir(char *old_str, char *new_str)
{
	int		i;
	char	*temp;

	i = -1;
	while (old_str[++i])
	{
		i = skip_quotes(old_str, i);
		if (old_str[i] == '<' || old_str[i] == '>')
		{
			if (old_str[i + 1] != ' ' && (old_str[i + 1] != '<'
					&& old_str[i + 1] != '>'))
			{
				temp = old_str;
				old_str = add_char_to_string(temp, new_str, ' ', i + 1);
				free(temp);
				new_str = (char *)malloc((ft_strlen(old_str)
							+ cnt_needed_sp(old_str) + 2) * sizeof(char));
			}
		}
	}
	return (old_str);
}

char	*handle_redir_symbols(char *s)
{
	char	*new_input;

	new_input = (char *)malloc((ft_strlen(s) + cnt_needed_sp(s) + 2)
			* sizeof (char));
	s = add_space_before_redir(s, new_input);
	new_input = (char *)malloc((ft_strlen(s) + cnt_needed_sp(s) + 2)
			* sizeof(char));
	s = add_space_after_redir(s, new_input);
	//TODO: any memory leaks here?
	return (s);
}
