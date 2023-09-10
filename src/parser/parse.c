/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emirzaza <emirzaza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 22:03:04 by emirzaza          #+#    #+#             */
/*   Updated: 2023/09/10 11:26:49 by emirzaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_spec_chr_comb(char **s, size_t *c, char *m1, 
				bool (*f)(char *, char *, int))
{
	char	*m2;

	if (c && ft_mode_diff(m1, "sp", 2))
		++(*c);
	while (*(++(*s)))
	{
		m2 = ft_check_special_chr(**s, *((*s) + 1), *((*s) - 1));
		if (f(m1, m2, ft_strlen(m2)))
			break ;
	}
}

static size_t	ft_wordlen(char *s)
{
	size_t	cnt;
	char	*mode;

	cnt = 0;
	while (*s && ft_isspace(*s))
		++s;
	if (*s && ++cnt)
		while (*s && !ft_isspace(*s))
			++s;
	while (*s)
	{
		mode = ft_check_special_chr(*s, *(s + 1), *(s - 1));
		ft_shift_special_chr(&s, mode);
		if (ft_mode_equal(mode, "sp", 2) || ft_mode_equal(mode, "nan", 3))
			ft_spec_chr_comb((char **)&s, &cnt, mode, ft_mode_diff);
		else if (ft_mode_equal(mode, "sq", 2) || ft_mode_equal(mode, "dq", 2))
			ft_spec_chr_comb((char **)&s, &cnt, mode, ft_mode_equal);
		else if (ft_mode_equal(mode, "esq", 3) || ft_mode_equal(mode, "edq", 3))
			ft_spec_chr_comb((char **)&s, &cnt, mode, ft_mode_equal);
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

	while (*s)
	{
		mode = ft_check_special_chr(*s, *(s + 1), *(s - 1));
		ft_shift_special_chr(&s, mode);
		from = (char *)s;
		if (ft_mode_equal(mode, "sp", 2) || ft_mode_equal(mode, "nan", 3))
			ft_spec_chr_comb((char **)&s, NULL, mode, ft_mode_diff);
		else if (ft_mode_equal(mode, "sq", 2) || ft_mode_equal(mode, "dq", 2))
			ft_spec_chr_comb((char **)&s, NULL, mode, ft_mode_equal);
		else if (ft_mode_equal(mode, "esq", 3) || ft_mode_equal(mode, "edq", 3))
			ft_spec_chr_comb((char **)&s, NULL, mode, ft_mode_equal);
		if (ft_mode_diff(mode, "sp", 2))
		{
			temp = ft_substr(from, 0, s - from);
			buf[i] = ft_removechr(temp, '\\');
			if (!buf[i++])
				return (ft_wordfree(buf, i));
		}
		ft_shift_special_chr(&s, mode);
	}
	buf[i] = NULL;
	return (buf);
}

char	**ft_cmd_split(char *s)
{
	int		i;
	char	*start;
	char	**buf;

	i = 0;
	if (!s || !ft_dcalloc((void **)(&buf), ft_wordlen(s) + 1, sizeof(char *)))
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
