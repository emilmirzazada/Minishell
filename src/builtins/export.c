/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emirzaza <emirzaza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 10:49:34 by emirzaza          #+#    #+#             */
/*   Updated: 2023/10/17 17:19:50 by emirzaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	validate_arg(char *str)
{
	int		i;
	char	*temp;

	i = -1;
	temp = ft_strtrim(str, "'");
	if (!temp)
		return (false);
	if (temp[0] == '=')
	{
		free(temp);
		return (printf("Invalid identifier for export\n"), false);
	}
	while (temp[++i] && temp[i] != '=')
	{
		if ((ft_isalpha(temp[i]) == 1) || ft_isdigit(temp[i]) == 1)
			return (printf("Invalid identifier for export\n"), false);
		if (ft_strchr("!@#$%^&*()+-", temp[i]) || ft_isspace(temp[i]) == 1)
			return (printf("Invalid identifier for export\n"), false);
	}
	free(temp);
	return (true);
}

static int	export_args(t_minishell *mini, t_cmd *cmd)
{
	int		i;
	t_env	*env;

	i = 0;
	while (cmd->args[++i])
	{
		if (validate_arg(cmd->args[i]))
		{
			env = ft_setenv(cmd->args[i]);
			ft_envadd_back(&mini->env, env);
		}
		else
			exit(1); // replace with perror_and_exit
	}
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
