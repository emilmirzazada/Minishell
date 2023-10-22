/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrottger <wrottger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 17:21:35 by wrottger          #+#    #+#             */
/*   Updated: 2023/10/12 15:08:53 by wrottger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_strcmp(char *str1, char *str2)
{
	size_t	i;

	i = 0;
	if (!str1 || !str2)
		return (1);
	while (str2[i] && str1[i])
	{
		if (str1[i] != str2[i])
			return (1);
		i++;
	}
	if (str2[i] != str1[i])
		return (1);
	return (0);
}
