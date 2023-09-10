/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emirzaza <emirzaza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 14:41:03 by emirzaza          #+#    #+#             */
/*   Updated: 2023/07/18 20:44:50 by emirzaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	get_num_length(int n)
{
	int	length;

	length = 0;
	if (n < 0)
	{
		n *= -1;
		length = 1;
	}
	while (n > 0)
	{
		n = (n / 10);
		length++;
	}
	return (length);
}

static	char	*allocate_and_fill(char	*res, char	*str, size_t size)
{
	res = ft_calloc(size, sizeof(char));
	if (!res)
		return (res);
	ft_strlcpy(res, str, 12);
	return (res);
}

char	*ft_itoa(int num)
{
	char	*res;
	int		length;

	res = "";
	if (num == -2147483648)
		return (allocate_and_fill(res, "-2147483648", 12));
	if (num == 0)
		return (allocate_and_fill(res, "0", 2));
	length = get_num_length(num);
	res = ft_calloc(length + 1, sizeof(char));
	if (!res)
		return (res);
	if (num < 0)
	{
		num *= -1;
		res[0] = '-';
	}
	res[length] = '\0';
	while (num > 0)
	{
		res[--length] = (num % 10) + '0';
		num = num / 10;
	}
	return (res);
}
