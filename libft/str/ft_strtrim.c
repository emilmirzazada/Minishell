/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emirzaza <emirzaza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 22:38:37 by emirzaza          #+#    #+#             */
/*   Updated: 2023/07/18 20:45:36 by emirzaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static	int	char_in_set(char c, const char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*res;
	int		start;
	int		end;
	int		i;

	start = 0;
	end = 0;
	while ((s1[start] && char_in_set(s1[start], set) != 0))
		start++;
	end = ft_strlen(s1);
	while ((end > start && char_in_set(s1[end - 1], set) != 0))
		end--;
	res = (char *)malloc(sizeof(char) * (end - start + 1));
	if (!res)
		return (res);
	i = 0;
	while (start < end)
	{
		res[i++] = s1[start++];
	}
	res[i] = '\0';
	return (res);
}
