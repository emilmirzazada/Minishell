/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrottger <wrottger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 11:23:09 by emirzaza          #+#    #+#             */
/*   Updated: 2023/10/31 13:17:10 by wrottger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**parse_arguments(char **arg, int *print_newline)
{
	*print_newline = 1;
	while (*arg && ft_strncmp(*arg, "-n", 2) == 0)
	{
		*print_newline = 0;
		arg++;
	}
	return (arg);
}

static void	print_arguments(char **arg)
{
	while (*arg)
	{
		ft_putstr_fd(*arg, 1);
		if (*(arg + 1))
			ft_putstr_fd(" ", 1);
		arg++;
	}
}

int	ft_echo(t_cmd *cmd)
{
	char	**arg;
	int		print_newline;

	arg = &(cmd->args[1]);
	arg = parse_arguments(arg, &print_newline);
	print_arguments(arg);
	if (print_newline)
		ft_putstr_fd("\n", 1);
	return (0);
}
