/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emirzaza <emirzaza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 10:49:34 by emirzaza          #+#    #+#             */
/*   Updated: 2023/10/29 15:28:46 by emirzaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	validate_arg(char *str)
{
	int		i;
	char	*temp;
	bool	first_char_is_set;

	i = -1;
	temp = ft_strtrim(str, "'");
	first_char_is_set = 0;
	if (!temp)
		return (false);
	if (temp[0] == '=')
	{
		free(temp);
		return (false);
	}
	while (temp[++i] && temp[i] != '=')
	{
		if ((first_char_is_set == false) && (ft_isalpha(temp[i]) == 1))
			first_char_is_set = true;
		if (first_char_is_set == false && ft_isdigit(temp[i]) == 1)
			return (false);
		if (ft_strchr("!@#$%^&*()+-", temp[i]) || ft_isspace(temp[i]) == 1)
			return (false);
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
			env = ft_set_raw_env(cmd->args[i]);
			ft_envadd_back(&mini->env, env);
		}
		else
		{
			ft_putstr_fd(" not a valid identifier\n", 2);
			clean_exit(mini, 1);
		}
	}
	set_env_array(mini);
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
