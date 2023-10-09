/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_tokens.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrottger <wrottger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 12:39:48 by emirzaza          #+#    #+#             */
/*   Updated: 2023/10/09 13:46:58 by wrottger         ###   ########.fr       */
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
		if (lex->token == TOK_WORD)
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

	if (((*lex)->token == TOK_IN || (*lex)->token == TOK_OUT)
		&& (*lex)->token != TOK_PIPE)
	{
		ft_putstr_fd((*lex)->value, 2);
		ft_putstr_fd("\n", 2);
		// if (handle_redir_tokens(new_cmd, lex))
		// 	return (1);
		*lex = (*lex)->next;
	}
	ft_putstr_fd("sep\n", 2);
	ft_putstr_fd((*lex)->value, 2);
	ft_putstr_fd("\n", 2);
	while (*lex && (*lex)->token != TOK_PIPE && (*lex)->token == TOK_WORD)
	{
		new_cmd->args[cmd_argc++] = ft_strdup((*lex)->value);
		*lex = (*lex)->next;
	}
	new_cmd->cmd = new_cmd->args[0];
	new_cmd->args[cmd_argc] = 0;
	return (0);
}
