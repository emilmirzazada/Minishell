/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emirzaza <emirzaza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 11:56:50 by emirzaza          #+#    #+#             */
/*   Updated: 2023/09/12 14:19:01 by emirzaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_set_null(void **ptr)
{
	if (!(ptr && *ptr))
		return ;
	free(*ptr);
	*ptr = NULL;
}

char	*ft_removechr(char	*str, char chr)
{
	char	*res;
	int		i;
	int		j;
	int		k;
	int		count;

	i = -1;
	count = 0;
	while (str[++i])
	{
		if (str[i] == chr)
			count++;
	}
	res = malloc(sizeof(char) * (ft_strlen(str) - count + 1));
	j = 0;
	k = 0;
	while (i-- > 0)
	{
		if (str[k] != chr)
			res[j++] = str[k];
		k++;
	}
	res[j] = 0;
	free(str);
	return (res);
}
