/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emirzaza <emirzaza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 22:03:04 by emirzaza          #+#    #+#             */
/*   Updated: 2023/10/15 18:21:07 by emirzaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_spec_chr_comb(char **s, char *m1,
				bool (*f)(char *, char *, int), bool *is_end)
{
	char	previous_chr;
	char	current_chr;
	char	next_chr;
	char	*m2;
	int		cnt;

	cnt = ft_mode_diff(m1, "sp", 2);
	previous_chr = '\0';
	while (!*is_end)
	{
		if (!iterate_string(s, is_end))
			break ;
		current_chr = **s;
		if (current_chr == '\0')
			next_chr = '\0';
		else
			next_chr = *((*s) + 1);
		m2 = ft_check_special_chr(current_chr, next_chr, previous_chr);
		if (f(m1, m2, strlen(m2)))
			break ;
		previous_chr = current_chr;
	}
	return (cnt);
}

static size_t	ft_wordlen(char *s)
{
	size_t	cnt;
	char	*mode;
	bool	is_end;

	is_end = false;
	cnt = 0;
	while (*s && ft_isspace(*s))
		++s;
	if (*s && ++cnt)
		while (*s && !ft_isspace(*s))
			++s;
	while (*s && !is_end)
	{
		mode = ft_check_special_chr(*s, *(s + 1), *(s - 1));
		ft_shift_special_chr(&s, mode);
		if (ft_mode_equal(mode, "sp", 2) || ft_mode_equal(mode, "nan", 3))
			cnt += ft_spec_chr_comb((char **)&s, mode, ft_mode_diff, &is_end);
		else if (ft_mode_equal(mode, "sq", 2) || ft_mode_equal(mode, "dq", 2))
			cnt += ft_spec_chr_comb((char **)&s, mode, ft_mode_equal, &is_end);
		else if (ft_mode_equal(mode, "esq", 3) || ft_mode_equal(mode, "edq", 3))
			cnt += ft_spec_chr_comb((char **)&s, mode, ft_mode_equal, &is_end);
		ft_shift_special_chr(&s, mode);
	}
	return (cnt);
}

static char	**ft_wordfree(char **s, int i)
{
	while (--i >= 0 && s[i])
		free_set_null((void **)(&(s[i])));
	free_set_null((void **)(&s));
	return (NULL);
}

char	**ft_wordout(char *s, char **buf, int i, char *temp)
{
	char	*from;
	char	*mode;
	bool	is_end;

	is_end = false;
	while (*s && !is_end)
	{
		mode = ft_check_special_chr(*s, *(s + 1), *(s - 1));
		from = ft_shift_special_chr(&s, mode);
		if (ft_mode_equal(mode, "sp", 2) || ft_mode_equal(mode, "nan", 3))
			ft_spec_chr_comb((char **)&s, mode, ft_mode_diff, &is_end);
		else if (ft_mode_equal(mode, "sq", 2) || ft_mode_equal(mode, "dq", 2))
			ft_spec_chr_comb((char **)&s, mode, ft_mode_equal, &is_end);
		else if (ft_mode_equal(mode, "esq", 3) || ft_mode_equal(mode, "edq", 3))
			ft_spec_chr_comb((char **)&s, mode, ft_mode_equal, &is_end);
		if (ft_mode_diff(mode, "sp", 2))
		{
			temp = ft_substr(from, 0, s - from);
			buf[i] = ft_removechr(temp, '\\');
			if (!buf[i++])
				return (ft_wordfree(buf, i));
		}
		ft_shift_special_chr(&s, mode);
	}
	return (buf[i] = NULL, buf);
}

char	**ft_input_split(char *s)
{
	int		i;
	char	*start;
	char	**buf;

	if (check_quotes(s) == -1)
	{
		printf("Minishell: Unclosed quote\n");
		return (NULL);
	}
	s = handle_redir_symbols(s);
	i = 0;
	if (!s || !ft_pcalloc((void **)(&buf), ft_wordlen(s) + 1, sizeof(char *)))
		return (NULL);
	while (*s && ft_isspace(*s))
		++s;
	if (*s)
	{
		start = (char *)s;
		while (*s && !ft_isspace(*s))
			++s;
		buf[i] = ft_substr(start, 0, (s - start));
		if (!buf[i++])
			return (ft_wordfree(buf, i));
	}
	return (ft_wordout(s, buf, i, NULL));
}
