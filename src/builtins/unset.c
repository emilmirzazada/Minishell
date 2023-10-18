/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emirzaza <emirzaza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 17:26:26 by emirzaza          #+#    #+#             */
/*   Updated: 2023/10/17 21:58:10 by emirzaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset_env_arg(t_env **env, char *key)
{
	t_env	**ptr;
	t_env	*temp;

	ptr = env;
	while (*ptr)
	{
		if (ft_strncmp(key, (*ptr)->key, ft_strlen((*ptr)->key)) == 0)
		{
			temp = *ptr;
			*ptr = temp->next;
			free(temp->key);
			free(temp->value);
			free(temp);
			return ;
		}
		else
			ptr = &((*ptr)->next);
	}
}

int	ft_unset(t_minishell *mini, t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->args[++i])
	{
		if (!validate_arg(cmd->args[i]))
			perror_exit("Invalid identifier for unset\n", mini, 1);
		else
		{
			unset_env_arg(&mini->env, cmd->args[i]);
			set_env_array(mini);
		}
	}
	return (0);
}
