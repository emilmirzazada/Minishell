/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emirzaza <emirzaza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 10:35:36 by emirzaza          #+#    #+#             */
/*   Updated: 2023/10/15 14:36:13 by emirzaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_setenv(char *key, char *value)
{
	t_env	*env;

	env = (t_env *)malloc(sizeof(t_env));
	ft_bzero(env, sizeof(*env));
	if (!env)
		return (NULL);
	env->key = ft_strdup(key);
	if (!value)
		env->value = ft_strdup("");
	else
		env->value = ft_strdup(value);
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

void	ft_env_init(t_minishell *mini, char **env)
{
	t_env	*tmp;
	char	*key;
	char	*value;
	char	*sep;
	int		i;

	if (!env)
	{
		return ;
	}
	mini->env = NULL;
	i = -1;
	while (env[++i])
	{
		sep = ft_strchr(env[i], '=');
		key = ft_substr(env[i], 0, sep - env[i]);
		value = ft_substr(sep + 1, 0, ft_strlen(sep + 1));
		tmp = ft_setenv(key, value);
		ft_envadd_back(&mini->env, tmp);
		free(key);
		free(value);
	}
}
