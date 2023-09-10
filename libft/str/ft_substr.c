/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emirzaza <emirzaza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 18:49:25 by emirzaza          #+#    #+#             */
/*   Updated: 2023/08/15 13:11:54 by emirzaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*sub;
	size_t	slen;

	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	slen = ft_strlen(s + start);
	if (slen < len)
		len = slen;
	sub = (char *)malloc(sizeof(*s) * (len + 1));
	if (!sub)
		return (NULL);
	i = -1;
	j = 0;
	while (s[++i])
	{
		if (i >= start && j < len)
		{
			sub[j] = s[i];
			j++;
		}
	}
	sub[j] = '\0';
	return (sub);
}
