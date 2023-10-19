/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emirzaza <emirzaza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 10:10:09 by emirzaza          #+#    #+#             */
/*   Updated: 2023/10/19 10:57:26 by emirzaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

bool	ft_atoi(const char *str, long *num)
{
	int		negative;

	*num = 0;
	negative = 0;
	if (!str)
		return (false);
	while (*str)
	{
		while (*num == 0 && (*str == '\n' || *str == '\t' || *str == '\f'
				|| *str == '\r' || *str == '\v' || *str == ' '))
			str++;
		if (*num == 0 && (*str == '-' || *str == '+'))
			if (*str++ == '-')
				negative++;
		while (*num == 0 && *str == '0')
			str++;
		if (*str >= '0' && *str <= '9')
			*num = *num * 10 + *str - '0';
		else
			return (false);
		str++;
	}
	if (negative % 2 == 1)
		*num *= -1;
	return (true);
}
