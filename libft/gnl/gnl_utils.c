/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emirzaza <emirzaza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 15:30:56 by emirzaza          #+#    #+#             */
/*   Updated: 2023/08/08 21:16:09 by emirzaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	gnl_strlcpy(char *dest, char *src, size_t size)
{
	size_t		remaining_size;
	size_t		src_length;

	src_length = ft_strlen(src);
	if (size == 0)
		return (src_length);
	remaining_size = size;
	while (*src != '\0' && remaining_size > 1)
	{
		*dest++ = *src++;
		remaining_size--;
	}
	*dest = '\0';
	return (src_length);
}

char	*ft_free_and_make_null(char	**str)
{
	free(*str);
	*str = NULL;
	return (NULL);
}

char	*gnl_strjoin(char *s1, char *s2)
{
	char	*res;
	int		j;
	char	*temp;

	if (s1 == 0)
	{
		s1 = (char *)malloc(sizeof(char) * 1);
		if (!s1)
			return (s1);
		s1[0] = '\0';
	}
	if (!s1 || !s2)
		return (NULL);
	res = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!res)
		return (ft_free_and_make_null(&s1));
	j = 0;
	temp = s1;
	while (*s1)
		res[j++] = *s1++;
	while (*s2)
		res[j++] = *s2++;
	res[j] = '\0';
	free(temp);
	return (res);
}
