/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emirzaza <emirzaza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 21:08:08 by emirzaza          #+#    #+#             */
/*   Updated: 2023/07/18 20:46:00 by emirzaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_list	*ft_lstmap(t_list *list, int (*f)(int), void (*del)(int))
{
	t_list	*new;
	t_list	*temp;

	new = NULL;
	if (list && f && del)
	{
		while (list)
		{
			temp = ft_lstnew(f(list->content));
			if (!temp)
			{
				ft_lstclear(&new, del);
				return (NULL);
			}
			ft_lstadd_back(&new, temp);
			temp = temp->next;
			list = list->next;
		}
		if (temp)
			ft_lstclear(&temp, del);
	}
	return (new);
}
