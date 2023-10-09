/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   std_io_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrottger <wrottger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 10:58:44 by wrottger          #+#    #+#             */
/*   Updated: 2023/10/09 11:11:52 by wrottger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	save_stdio(t_stdio std_io)
{
	std_io.stdout = dup(STDOUT_FILENO);
	std_io.stdin = dup(STDIN_FILENO);
}

void	load_stdio(t_stdio std_io)
{
	dup2(io.stdout, STDOUT_FILENO);
	dup2(io.stdin, STDIN_FILENO);
}
