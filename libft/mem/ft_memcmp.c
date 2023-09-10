/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emirzaza <emirzaza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 18:40:26 by emirzaza          #+#    #+#             */
/*   Updated: 2023/07/18 20:44:34 by emirzaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_memcmp(const void *str1, const void *str2, size_t n)
{
	size_t	i;
	char	*str1c;
	char	*str2c;

	str1c = (char *)str1;
	str2c = (char *)str2;
	i = 0;
	while (i < n)
	{
		if (str1c[i] != str2c[i])
			return ((unsigned char)str1c[i] - (unsigned char)str2c[i]);
		i++;
	}
	return (0);
}
