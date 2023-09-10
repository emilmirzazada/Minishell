/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emirzaza <emirzaza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 20:57:24 by emirzaza          #+#    #+#             */
/*   Updated: 2023/07/18 20:45:00 by emirzaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	char	new_line;

	new_line = '\n';
	while (*s)
	{
		write (fd, &*s++, 1);
	}
	write (fd, &new_line, 1);
}
