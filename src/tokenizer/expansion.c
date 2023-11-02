/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emirzaza <emirzaza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 19:33:09 by emirzaza          #+#    #+#             */
/*   Updated: 2023/11/02 18:48:54 by emirzaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*place_value(char *temp, char *value, int *t, bool heredoc)
{
	int		temp_len;
	int		value_len;
	char	*new_temp;

	if (value && value[0] != '\0')
	{
		if (!heredoc)
			value = embrace_value(value);
		if (temp && temp[0] == 0)
			temp_len = 1;
		else
			temp_len = ft_strlen(temp);
		value_len = ft_strlen(value);
		*t += value_len;
		new_temp = ft_calloc((temp_len + *t + value_len), sizeof(char));
		if (!new_temp)
			return (NULL);
		ft_strlcpy(new_temp, temp, temp_len + value_len + 1);
		ft_strlcat(new_temp, value, temp_len + value_len + 1);
		free(value);
		free(temp);
		return (new_temp);
	}
	free(value);
	return (free(temp), ft_strdup("\0"));
}

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

char	*expand_dollar_special(t_minishell *mini, char c, int *i)
{
	char	*value;

	value = NULL;
	if (c == '?' || c == '$')
	{
		if (g_signal_num == 2)
		{
			value = ft_itoa(1);
			g_signal_num = 0;
		}
		else if (c == '?')
			value = ft_itoa(mini->exit_code);
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
		*value = expand_dollar_special(mini, s[i], &i);
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

char	*expand(t_minishell *mini, bool heredoc)
{
	char	*temp;
	char	*value;
	int		i;
	int		t;

	i = 0;
	t = 0;
	value = NULL;
	temp = ft_calloc(ft_strlen(mini->input) + 1, sizeof(char));
	if (!temp)
		return (NULL);
	while (mini->input[i] != '\0')
	{
		if (mini->input[i] == '$')
		{
			i += search_variable(mini, &mini->input[i], &value);
			temp = place_value(temp, value, &t, heredoc);
		}
		else
			place_rest_of_string(mini->input, temp, &i, &t);
	}
	return (temp);
}
