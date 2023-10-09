/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_tokens.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emirzaza <emirzaza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 12:39:48 by emirzaza          #+#    #+#             */
/*   Updated: 2023/10/09 19:07:18 by emirzaza         ###   ########.fr       */
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
	new_cmd->files = NULL;
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
	while (lex && lex->token != TOK_WORD)
		lex = lex->next;
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

t_cmd	*init_new_command(t_minishell *mini, t_lex *lex, int *cmd_argc)
{
	t_cmd	*new_cmd;
	t_lex	*tmp_lex;

	new_cmd = ft_create_command(mini);
	if (!new_cmd)
		return (NULL);
	tmp_lex = lex;
	if (ft_cmd_args_malloc(new_cmd, tmp_lex))
		return (NULL);
	*cmd_argc = 0;
	return (new_cmd);
}

void	parse_cmd_files(t_cmd *cmd, t_lex	**lex, t_lex **temp)
{
	while ((*temp) && (*temp)->token != TOK_PIPE)
	{
		if ((*temp)->token == TOK_IN || (*temp)->token == TOK_OUT)
		{
			if (handle_redir_tokens(cmd, temp))
				return ;
			*lex = (*lex)->next;
		}
		(*temp) = (*temp)->next;
	}
	if ((*lex)->token == TOK_FILE)
		*lex = (*lex)->next;
}

int	handle_word_tokens(t_minishell *mini, t_lex **lex)
{
	t_cmd	*new_cmd;
	int		cmd_argc;
	t_lex	**temp;

	temp = lex;
	lex = &mini->lex;
	new_cmd = NULL;
	while (*lex)
	{
		if ((*lex)->token == TOK_PIPE || new_cmd == NULL)
			new_cmd = init_new_command(mini, *lex, &cmd_argc);
		parse_cmd_files(new_cmd, lex, temp);
		while (*lex && (*lex)->token != TOK_PIPE && (*lex)->token == TOK_WORD)
		{
			new_cmd->args[cmd_argc++] = ft_strdup((*lex)->value);
			if ((*lex)->next && (*lex)->next->token != TOK_OUT)
				*lex = (*lex)->next;
			else
				break ;
		}
		if (*lex && ((*lex)->token == TOK_PIPE || new_cmd == NULL))
		{
			new_cmd->cmd = new_cmd->args[0];
			new_cmd->args[cmd_argc] = 0;
			new_cmd = init_new_command(mini, *lex, &cmd_argc);
			*temp =  (*lex)->next;
		}
		if (*lex)
		{
			if (!((*lex)->next))
			{
				new_cmd->cmd = new_cmd->args[0];
				new_cmd->args[cmd_argc] = 0;
				return (0);
			}
			else
				*lex = (*lex)->next;
		}
		else
		{
			new_cmd->cmd = new_cmd->args[0];
			new_cmd->args[cmd_argc] = 0;
		}
	}
	
	return (0);
}
