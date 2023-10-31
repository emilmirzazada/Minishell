/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emirzaza <emirzaza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 10:10:09 by emirzaza          #+#    #+#             */
/*   Updated: 2023/10/31 19:39:13 by emirzaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

const char	*atoi_helper(const char *str, long *num, int *negative)
{
	while (*num == 0 && (*str == '\n' || *str == '\t' || *str == '\f'
			|| *str == '\r' || *str == '\v' || *str == ' '))
		str++;
	if (*num == 0 && (*str == '-' || *str == '+'))
		if (*str++ == '-')
			*negative += 1;
	while (*num == 0 && *str == '0')
		str++;
	return (str);
}

bool	ft_atoi(const char *str, long *num)
{
	int		negative;
	bool	status;

	*num = 0;
	status = true;
	negative = 0;
	if (!str)
		return (false);
	while (*str)
	{
		str = atoi_helper(str, num, &negative);
		if (*str >= '0' && *str <= '9')
			*num = *num * 10 + *str - '0';
		else
		{
			if (*str == 0)
				break ;
			else
				status = false;
		}
		str++;
	}
	if (negative % 2 == 1)
		*num *= -1;
	return (status);
}
