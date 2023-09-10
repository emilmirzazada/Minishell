/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emirzaza <emirzaza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 16:18:36 by emirzaza          #+#    #+#             */
/*   Updated: 2023/08/08 10:09:04 by emirzaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_strncmp(char *str1, char *str2, size_t n)
{
	size_t	i;
	size_t	str1len;
	size_t	str2len;

	str1len = ft_strlen(str1);
	str2len = ft_strlen(str2);
	if (n == 0)
		return (0);
	if (str1len == 0 && str2len > 0)
		return (str1len - str2len);
	i = 0;
	while (i < n)
	{
		if (str1[i] != str2[i] || str1[i] == '\0')
			return ((unsigned char)(str1[i]) - (unsigned char)str2[i]);
		i++;
	}
	return (0);
}
