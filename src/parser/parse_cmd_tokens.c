/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_tokens.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emirzaza <emirzaza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 12:39:48 by emirzaza          #+#    #+#             */
/*   Updated: 2023/10/05 14:21:45 by emirzaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_command_addback(t_cmd **lst, t_cmd *new)
{
	t_cmd	**ptr;

	ptr = lst;
	while (*ptr)
		ptr = &(*ptr)->next;
	*ptr = new;
}

t_cmd	*ft_create_command(t_minishell *mini)
{
	t_cmd		*new_cmd;

	new_cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new_cmd)
		return (NULL);
	new_cmd->next = NULL;
	ft_command_addback(&(mini->cmd), new_cmd);
	return (new_cmd);
}

int	ft_cmd_args_malloc(t_cmd *cmd, t_lex *lex)
{
	t_lex	*temp;
	int		argc;

	temp = lex;
	argc = 0;
	while (lex && lex->token != TOK_PIPE)
	{
		if (lex->token == TOK_ARG)
			argc++;
		lex = lex->next;
	}
	cmd->args = malloc(sizeof(char **) * (argc + 2));
	if (!(cmd->args))
		return (1);
	return (0);
}

int	handle_word_tokens(t_minishell *mini, t_lex **lex)
{
	t_lex	*tmp_lex;
	t_cmd	*new_cmd;
	int		cmd_argc;

	new_cmd = ft_create_command(mini);
	if (!new_cmd)
		return (1);
	tmp_lex = *lex;
	if (ft_cmd_args_malloc(new_cmd, tmp_lex))
		return (1);
	cmd_argc = 0;
	while (*lex && (*lex)->token != TOK_PIPE && (*lex)->token == TOK_ARG)
	{
		new_cmd->args[cmd_argc++] = ft_strdup((*lex)->value);
		if ((*lex)->next != NULL && (*lex)->next->token == TOK_ARG)
			*lex = (*lex)->next;
		else
			break ;
	}
	new_cmd->args[cmd_argc] = 0;
	return (0);
}
