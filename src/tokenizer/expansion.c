/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emirzaza <emirzaza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 19:33:09 by emirzaza          #+#    #+#             */
/*   Updated: 2023/10/05 19:41:50 by emirzaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//returns null terminated string in case no match found
char	*ft_getenv(t_env *lst, char *key)
{
	char	*value;

	while (lst)
	{
		if (ft_strncmp(key, lst->key, ft_strlen(lst->key)) == 0
			&& ft_strlen(lst->key) == ft_strlen(key))
		{
			return (ft_strdup(lst->value));
		}
		lst = lst->next;
	}
	value = malloc(1);
	if (!value)
		return (NULL);
	ft_bzero(value, 1);
	return (value);
}

int	search_variable(t_minishell *mini, char *s, char **value)
{
	int		i;
	char	*name;

	i = 1;
	name = NULL;
	if (s[i] == '?' || s[i] == ' ' || s[i] == '\0')
		*value = last_command_exit_code(s[i], &i);
	else
	{
		i += expansion_end_check(&s[i], " <>|\"'$[]{}()");
		name = get_name(&s[1], i);
		if (!name)
			return (i);
		*value = ft_getenv(mini->env, name);
		free(name);
	}
	return (i);
}

char	*expand(t_minishell *mini, char *s)
{
	char	*temp;
	char	*value;
	int		i;
	int		t;

	i = 0;
	t = 0;
	value = NULL;
	temp = malloc(ft_strlen(s) * sizeof(char) + 1);
	if (!temp)
		return (NULL);
	while (s[i] != '\0')
	{
		if (s[i] == '$')
		{
			temp[t] = '\0';
			i += search_variable(mini, &s[i], &value);
			t += ft_strlen(value);
			temp = place_value(temp, value, s);
		}
		else
			place_rest_of_string(s, temp, &i, &t);
	}
	temp[t] = '\0';
	return (temp);
}
