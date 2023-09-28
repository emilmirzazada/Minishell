/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 16:56:14 by marvin            #+#    #+#             */
/*   Updated: 2023/09/28 16:56:14 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	print_commands(t_minishell *mini)
{
	t_cmd	*tmp;
	char	**tmp_args;

	tmp = mini->cmd;
	while (tmp)
	{
		tmp_args = tmp->args;
		while (*tmp_args)
		{
			ft_putstr_fd(*tmp_args, 2);
			ft_putstr_fd("\n", 2);
			tmp_args++; 
		}
		ft_putstr_fd("----\n", 2);
		tmp = tmp->next;
	}
}

void    *execute_commands(t_minishell *mini)
{
    print_commands(mini);
    return (mini);
}
