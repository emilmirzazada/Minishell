/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emirzaza <emirzaza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 17:01:00 by emirzaza          #+#    #+#             */
/*   Updated: 2023/07/18 20:44:39 by emirzaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	char	*destc;
	char	*srcc;

	if (!src && !dest)
		return (NULL);
	if (src > dest)
		dest = ft_memcpy(dest, src, len);
	else
	{
		destc = (char *)dest;
		srcc = (char *)src;
		while (len--)
		{
			destc[len] = srcc[len];
		}
	}
	return (dest);
}
