/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_reset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emirzaza <emirzaza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 11:59:02 by emirzaza          #+#    #+#             */
/*   Updated: 2023/10/28 12:00:55 by emirzaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reset_signals(t_minishell *mini)
{
	if (g_signal_num != 0)
	{
		mini->exit_code = g_signal_num;
		g_signal_num = 0;
	}
}
