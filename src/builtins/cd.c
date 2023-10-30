/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emirzaza <emirzaza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 19:14:43 by emirzaza          #+#    #+#             */
/*   Updated: 2023/10/27 14:50:19 by emirzaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	update_env(t_env *env, char *key, char *value)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strnstr(tmp->key, key, ft_strlen(key)) != 0)
		{
			if (value)
			{
				tmp->value = value;
			}
			else
			{
				tmp->value = ft_strdup("\0");
			}
		}
		tmp = tmp->next;
	}
}

static	void	update_pwd_env(t_minishell *mini)
{
	char	*old_pwd;
	char	*old_old_pwd;

	old_pwd = find_env(mini->env, "PWD");
	old_old_pwd = find_env(mini->env, "OLDPWD");
	free(old_old_pwd);
	update_env(mini->env, "OLDPWD", ft_strdup(old_pwd));
	update_env(mini->env, "PWD", getcwd(NULL, 0));
	set_env_array(mini);
	free(old_pwd);
}

static	bool	ft_cd_home(t_minishell *mini, t_cmd *cmd)
{
	char	*home;

	if (cmd->args[1] != 0)
		return (false);
	else if (cmd->args[1] == 0)
	{
		home = find_env(mini->env, "HOME");
		if (home)
		{
			update_pwd_env(mini);
			chdir(home);
		}
	}
	return (true);
}

int	ft_cd(t_minishell *mini, t_cmd *cmd)
{
	if (!ft_cd_home(mini, cmd))
	{
		if (chdir(cmd->args[1]) == 0)
			update_pwd_env(mini);
		else
		{
			ft_putstr_fd("Error: Path not found\n", 2);
			return (1);
		}
	}
	return (0);
}
