/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emirzaza <emirzaza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 15:38:55 by emirzaza          #+#    #+#             */
/*   Updated: 2023/09/08 12:53:17 by emirzaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_list	*ft_lstnew(int content)
{
	t_list	*lst;

	lst = malloc(1 * sizeof(t_list));
	if (!lst)
		return (lst);
	lst -> content = content;
	lst -> index = -1;
	lst -> next = NULL;
	return (lst);
}
