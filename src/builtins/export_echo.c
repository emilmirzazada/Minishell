/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_echo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emirzaza <emirzaza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 11:27:34 by emirzaza          #+#    #+#             */
/*   Updated: 2023/10/17 11:28:04 by emirzaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_key(char *str)
{
	char	*sep;
	char	*key;

	sep = ft_strchr(str, '=');
	key = ft_substr(str, 0, sep - str);
	return (key);
}

int	cmp_keys(char *env1, char *env2)
{
	char	*key1;
	char	*key2;
	int		res;

	key1 = get_key(env1);
	key2 = get_key(env2);
	if (ft_strlen(key1) > ft_strlen(key2))
		res = ft_strncmp(key1, key2, ft_strlen(key1));
	else
		res = ft_strncmp(key1, key2, ft_strlen(key2));
	free(key1);
	free(key2);
	return (res);
}

void	sort_env_arr(t_minishell *mini)
{
	int		i;
	int		j;
	char	**env;
	char	*temp;

	i = -1;
	env = mini->env_arr;
	while (env[++i])
	{
		j = -1;
		while (env[++j])
		{
			if (j > 0 && cmp_keys(env[j], env[j - 1]) < 0)
			{
				temp = ft_strdup(env[j - 1]);
				free(env[j - 1]);
				env[j - 1] = env[j];
				env[j] = temp;
			}
		}
	}
}

void	export_echo_sorted(t_minishell *mini)
{
	t_env	*temp;

	sort_env_arr(mini);
	temp = ft_env_init(mini->env_arr);
	while (temp)
	{
		if (temp->key[0] && temp->key[0] != '_')
		{
			printf("declare -x %s", temp->key);
			if (temp->value[0] != '\0')
				printf("=\"%s\"", temp->value);
			printf("\n");
		}
		temp = temp->next;
	}
}