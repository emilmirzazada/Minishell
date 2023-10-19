/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emirzaza <emirzaza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 10:35:36 by emirzaza          #+#    #+#             */
/*   Updated: 2023/10/18 21:45:27 by emirzaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_set_raw_env(char *env_str)
{
	t_env	*env;
	char	*key;
	char	*value;
	char	*sep;

	sep = ft_strchr(env_str, '=');
	key = ft_substr(env_str, 0, sep - env_str);
	if (sep)
		value = ft_substr(sep + 1, 0, ft_strlen(sep + 1));
	env = (t_env *)ft_calloc(sizeof(t_env), 1);
	if (!env)
		return (NULL);
	env->key = ft_strdup(key);
	if (!value)
		env->value = ft_strdup("");
	else
		env->value = ft_strdup(value);
	free(key);
	free(value);
	env->next = NULL;
	return (env);
}

int	ft_env(t_minishell *mini)
{
	t_env	*env;

	env = mini->env;
	while (env)
	{
		if (env->value && env->value[0] != '\0')
			printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
	return (0);
}

void	ft_replace_existing_env(t_env *lst, t_env *new)
{
	if ((lst)->value)
		free((lst)->value);
	if (!new->value)
		(lst)->value = ft_strdup("");
	else
		(lst)->value = ft_strdup(new->value);
	free(new->value);
	free(new->key);
	free(new);
}

void	ft_envadd_back(t_env **lst, t_env *new)
{
	t_env	**ptr;

	ptr = lst;
	while (*ptr)
	{
		if (ft_strncmp((*ptr)->key, new->key, ft_strlen(new->key)) == 0 \
		&& ft_strlen(new->key) == ft_strlen((*ptr)->key))
		{
			ft_replace_existing_env(*ptr, new);
			return ;
		}
		ptr = &(*ptr)->next;
	}
	*ptr = new;
}

t_env	*ft_env_init(char **env)
{
	t_env	*tmp;
	int		i;
	t_env	*lst;

	if (!env)
		return (NULL);
	lst = NULL;
	i = -1;
	while (env[++i])
	{
		tmp = ft_set_raw_env(env[i]);
		ft_envadd_back(&lst, tmp);
	}
	return (lst);
}
