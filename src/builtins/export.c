/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emirzaza <emirzaza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 10:49:34 by emirzaza          #+#    #+#             */
/*   Updated: 2023/10/17 11:32:44 by emirzaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	export_args(t_minishell *mini, t_cmd *cmd)
{
	int	i;

	// i = -1;
	// while (cmd->args[++i])
	// {
	// }
	return (0);
}

int	ft_export(t_minishell *mini, t_cmd *cmd)
{
	if (!cmd->args[1])
	{
		export_echo_sorted(mini);
		return (0);
	}
	else
		return (export_args(mini, cmd));
}

// if value is null it should only print key in export