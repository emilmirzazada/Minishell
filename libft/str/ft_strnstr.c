/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emirzaza <emirzaza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 18:50:07 by emirzaza          #+#    #+#             */
/*   Updated: 2023/07/18 20:45:31 by emirzaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	litlen;
	size_t	cnt;

	litlen = ft_strlen(little);
	if (litlen == 0)
		return ((char *)big);
	while (*big && len > 0 && litlen <= ft_strlen(big))
	{
		cnt = 0;
		if (*big == *little)
		{
			while (*(big + cnt) && *little + cnt == *big + cnt && len - cnt > 0)
			{
				if (cnt == litlen - 1 && *(little + cnt) == *(big + cnt))
					return ((char *)(big));
				cnt += 1;
			}
		}
		big++;
		len--;
	}
	return (0);
}
