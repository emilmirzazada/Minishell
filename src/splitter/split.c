/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emirzaza <emirzaza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 22:03:04 by emirzaza          #+#    #+#             */
/*   Updated: 2023/10/22 23:18:04 by emirzaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_split	*ft_create_split(t_minishell *mini, char *arg)
{
	t_split		*new_split;

	new_split = (t_split *)malloc(sizeof(t_split));
	if (!new_split)
		return (NULL);
	*new_split = (t_split){0};
	new_split->arg = arg;
	ft_split_addback(&(mini->split), new_split);
	return (new_split);
}

char	*split_arg(char *s, int *i, int len)
{
	char	*arg;

	arg = NULL;
	if (s[*i] == '\'' || s[*i] == '"')
		arg = split_quotes(&s[*i], i, s[*i]);
	else if (*i <= len && (s[*i] == '|' || s[*i] == ' '))
		arg = split_pipe(&s[*i], i, s[*i]);
	else if (*i <= len)
		arg = split_word(s, i);
	return (arg);
}

char	*substring_arg(t_minishell *mini, char *arg, char *l_arg, char l_char)
{
	t_split	*split;
	char	*last_arg;
	char	*new_arg;

	last_arg = arg;
	split = NULL;
	if (arg[0] != ' ')
	{
		if (l_char != ' ')
		{
			new_arg = ft_strjoin(l_arg, arg);
			if (new_arg)
			{
				split = ft_create_split(mini, arg);
				split->arg = new_arg;
				remove_split(&mini->split, l_arg);
			}
		}
		else
			split = ft_create_split(mini, arg);
	}
	if (split)
		last_arg = split->arg;
	return (last_arg);
}

bool	ft_input_split(t_minishell *mini, char *s)
{
	int		i;
	char	*arg;
	int		len;
	char	l_char;
	char	*l_arg;

	i = 0;
	l_arg = NULL;
	l_char = ' ';
	len = ft_strlen(s);
	if (check_quotes(s) == -1)
		return (printf("Minishell: Unclosed quote\n"), false);
	s = handle_redir_symbols(s);
	while (i <= len && s[i] != '\0')
	{
		arg = split_arg(s, &i, len);
		if (i <= len && arg && arg[0] != '\0')
		{
			l_arg = substring_arg(mini, arg, l_arg, l_char);
			l_char = s[i];
		}
	}
	return (true);
}

//printf("|%s| --- |%c| \n", arg, s[i]);
// echo "'$HOME'"
// ctrl+C and ctrl+D should work in heredoc
// handle | | |
//printf("|%s| --- |%c| \n", arg, s[i]);