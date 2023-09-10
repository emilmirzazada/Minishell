/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emirzaza <emirzaza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 17:28:08 by emirzaza          #+#    #+#             */
/*   Updated: 2023/07/18 20:45:10 by emirzaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strdup(const char *s)
{
	char	*target;
	int		i;

	target = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (target == NULL)
		return (target);
	i = 0;
	while (s[i])
	{
		target[i] = s[i];
		i++;
	}
	target[i] = '\0';
	return (target);
}
