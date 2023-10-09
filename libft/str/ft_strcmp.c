/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrottger <wrottger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 17:21:35 by wrottger          #+#    #+#             */
/*   Updated: 2023/10/05 17:30:47 by wrottger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_strcmp(char *str1, char *str2)
{
	size_t	i;
	size_t	str1len;
	size_t	str2len;

	str1len = ft_strlen(str1);
	str2len = ft_strlen(str2);
	if (str1len == 0 && str2len > 0)
		return (str1len - str2len);
	i = 0;
	while (str2[i] || str1[i])
	{
		if (str1[i] != str2[i] || str1[i] == '\0')
			return ((unsigned char)(str1[i]) - (unsigned char)str2[i]);
		i++;
	}
	return (0);
}
