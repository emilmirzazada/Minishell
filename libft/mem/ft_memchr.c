/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emirzaza <emirzaza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 17:29:11 by emirzaza          #+#    #+#             */
/*   Updated: 2023/07/18 20:44:24 by emirzaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	char		ch;
	const char	*strc;

	ch = (char)c;
	strc = (char *)str;
	while (n > 0)
	{
		if (*strc == ch)
			return ((void *)strc);
		strc++;
		n--;
	}
	return (0);
}
