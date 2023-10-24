/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emirzaza <emirzaza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 19:33:09 by emirzaza          #+#    #+#             */
/*   Updated: 2023/10/24 18:06:57 by emirzaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//returns null terminated string in case no match found
char	*ft_getenv(t_env *lst, char *key)
{
	char	*value;
	t_env	*temp;

	temp = lst;
	while (temp)
	{
		if (ft_strncmp(key, temp->key, ft_strlen(temp->key)) == 0
			&& ft_strlen(temp->key) == ft_strlen(key))
		{
			return (ft_strdup(temp->value));
		}
		temp = temp->next;
	}
	value = malloc(1);
	if (!value)
		return (NULL);
	ft_bzero(value, 1);
	return (value);
}

char	*expand_dollar_special(char c, int *i)
{
	char	*value;

	value = NULL;
	if (c == '?' || c == '$')
	{
		if (c == '?')
			value = ft_itoa(g_exit_code);
		else
			value = ft_itoa(65717);
		*i = *i + 1;
	}
	else if (c == ' ')
	{
		value = ft_strdup("$ ");
		*i = *i + 1;
	}
	else if (c == '\0' || c == '"')
		value = ft_strdup("$");
	return (value);
}

int	search_variable(t_minishell *mini, char *s, char **value)
{
	int		i;
	char	*name;

	i = 1;
	name = NULL;
	if (s[i] == '?' || s[i] == ' ' || s[i] == '\0'
		|| s[i] == '$' || s[i] == '"')
		*value = expand_dollar_special(s[i], &i);
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

char	*expand(t_minishell *mini)
{
	char	*temp;
	char	*value;
	int		i;
	int		t;

	i = 0;
	t = 0;
	value = NULL;
	temp = malloc(ft_strlen(mini->input) * sizeof(char) + 1);
	if (!temp)
		return (NULL);
	while (mini->input[i] != '\0')
	{
		if (mini->input[i] == '$')
		{
			temp[t] = '\0';
			i += search_variable(mini, &mini->input[i], &value);
			temp = place_value(temp, value, mini->input, &t);
		}
		else
			place_rest_of_string(mini->input, temp, &i, &t);
	}
	return (temp[t] = '\0', temp);
}
