/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pcalloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emirzaza <emirzaza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 11:51:11 by emirzaza          #+#    #+#             */
/*   Updated: 2023/09/10 11:51:26 by emirzaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_pcalloc(void **ptr, size_t cnt, size_t n)
{
	*ptr = (void *)malloc(cnt * n);
	if (!*ptr)
		return (-1);
	ft_memset(*ptr, 0, cnt * n);
	return (1);
}