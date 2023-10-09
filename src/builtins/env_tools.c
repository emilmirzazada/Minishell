/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrottger <wrottger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 10:07:21 by wrottger          #+#    #+#             */
/*   Updated: 2023/10/09 11:54:05 by wrottger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_env(t_env *lst, char *key)
{
	t_env	*ptr;

	ptr = lst;
	while (1)
	{
		if (ft_strncmp(ptr->key, key, ft_strlen(key) + 1) == 0)
		{
			return (ptr->value);
		}
		if (ptr->next == NULL)
			return (NULL);
		ptr = ptr->next;
	}
}

static char	**create_env_array(t_env	*env, int length)
{
	char	*temp1;
	char	*temp2;
	char	**env_arr;
	t_env	*temp;

	env_arr = malloc(sizeof(char *) * (length + 1));
	if (!env_arr)
	{
		ft_putstr_fd("Malloc failed in set_env_array\n", 2);
		return (env_arr);
	}
	length = 0;
	temp = env;
	while (temp)
	{
		temp1 = ft_strjoin(temp->key, "=");
		temp2 = ft_strjoin(temp1, temp->value);
		free(temp1);
		env_arr[length++] = temp2;
		temp = temp->next;
	}
	env_arr[length] = NULL;
	return (env_arr);
}

void	set_env_array(t_minishell *mini)
{
	t_env	*temp;
	int		length;

	temp = mini->env;
	length = 0;
	while (temp)
	{
		length++;
		temp = temp->next;
	}
	mini->env_arr = create_env_array(mini->env, length);
}
