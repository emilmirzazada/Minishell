/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emirzaza <emirzaza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 12:20:29 by emirzaza          #+#    #+#             */
/*   Updated: 2023/07/18 20:45:23 by emirzaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
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
