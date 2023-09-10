/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emirzaza <emirzaza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 17:01:00 by emirzaza          #+#    #+#             */
/*   Updated: 2023/07/18 20:44:17 by emirzaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	int					i;
	unsigned char		*dest_temp;
	unsigned char		*src_temp;

	if (!src && !dest)
		return (NULL);
	i = 0;
	dest_temp = (unsigned char *)dest;
	src_temp = (unsigned char *)src;
	while (n > 0)
	{
		dest_temp[i] = src_temp[i];
		i++;
		n--;
	}
	return (dest);
}
