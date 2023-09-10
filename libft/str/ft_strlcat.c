/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emirzaza <emirzaza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 15:55:19 by emirzaza          #+#    #+#             */
/*   Updated: 2023/07/18 20:45:21 by emirzaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t maxlen)
{
	size_t	srclen;
	size_t	dstlen;

	srclen = ft_strlen(src);
	dstlen = ft_strlen(dst);
	if (dstlen >= maxlen)
		return (maxlen + srclen);
	if (dstlen + srclen < maxlen)
	{
		ft_strlcpy(dst + dstlen, src, srclen + 1);
	}
	else
	{
		ft_strlcpy(dst + dstlen, src, maxlen - dstlen);
	}
	return (dstlen + srclen);
}
