/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emirzaza <emirzaza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 10:04:24 by emirzaza          #+#    #+#             */
/*   Updated: 2023/10/15 18:19:34 by emirzaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_isspace(int c)
{
	return (c == ' ' || c == '\n' || c == '\r'
		|| c == '\v' || c == '\f' || c == '\t');
}

bool	ft_mode_equal(char *m1, char *m2, int len)
{
	return (!ft_strncmp(m1, m2, len));
}

bool	ft_mode_diff(char *m1, char *m2, int len)
{
	return (ft_strncmp(m1, m2, len));
}

char	*ft_shift_special_chr(char **s, char *mode)
{
	if (ft_mode_equal(mode, "sq", 2) || ft_mode_equal(mode, "dq", 2))
		++(*s);
	if (ft_mode_equal(mode, "esq", 3) || ft_mode_equal(mode, "edq", 3))
		*s += 2;
	return (*s);
}

char	*ft_check_special_chr(int c1, int c2, int c0)
{
	if (ft_isspace(c1))
		return ("sp");
	else if (c1 == '\'' && c0 != '\\')
		return ("sq");
	else if (c1 == '\"' && c0 != '\\')
		return ("dq");
	else if (c1 == '\\' && c2 == '\'')
		return ("esq");
	else if (c1 == '\\' && c2 == '\"')
		return ("edq");
	else
		return ("nan");
}
