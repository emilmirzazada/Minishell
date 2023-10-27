/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_lists.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emirzaza <emirzaza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 11:41:13 by emirzaza          #+#    #+#             */
/*   Updated: 2023/10/27 14:03:28 by emirzaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_commands(t_cmd *list)
{
	t_cmd	*tmp;

	while (list)
	{
		tmp = list;
		list = list->next;
		free_command(tmp);
	}
}

void	free_double_char(char **arr)
{
	int	size;

	if (arr == NULL)
		return ;
	size = 0;
	while (arr[size] != NULL)
	{
		free(arr[size]);
		arr[size] = NULL;
		size++;
	}
	free (arr[size]);
	free(arr);
}

void	free_splits(t_split *list)
{
	t_split	*tmp;

	while (list)
	{
		tmp = list;
		list = list->next;
		free(tmp->arg);
		free(tmp);
		tmp = NULL;
	}
}

void	free_lex(t_lex *list)
{
	t_lex	*tmp;

	while (list)
	{
		tmp = list;
		list = list->next;
		if (tmp->value)
			free(tmp->value);
		free(tmp);
		tmp = NULL;
	}
}

void	free_env(t_env *list)
{
	t_env	*tmp;

	while (list)
	{
		tmp = list;
		list = list->next;
		if (tmp->value)
			free(tmp->value);
		if (tmp->key)
			free(tmp->key);
		free(tmp);
		tmp = NULL;
	}
}
