/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrottger <wrottger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 10:07:21 by wrottger          #+#    #+#             */
/*   Updated: 2023/10/05 11:15:56 by wrottger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_env(t_env *lst, char *key)
{
	t_env	*ptr;

	ptr = lst;
	while (1)
	{
		if (ft_strncmp(ptr->key, key, ft_strlen(key) + 1) == 0)
		{
			return (ptr->value);
		}
		if (ptr->next == NULL)
			return (NULL);
		ptr = ptr->next;
	}
}
