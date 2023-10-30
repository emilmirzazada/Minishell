/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_reset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emirzaza <emirzaza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 11:59:02 by emirzaza          #+#    #+#             */
/*   Updated: 2023/10/29 15:04:30 by emirzaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reset_signals(t_minishell *mini)
{
	if (g_signal_num != 0)
	{
		if (g_signal_num == 2)
			mini->exit_code = 1;
		else if (g_signal_num == 130)
			mini->exit_code = 130;
		else if (g_signal_num == 131)
			mini->exit_code = 131;
		g_signal_num = 0;
	}
}
