/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emirzaza <emirzaza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 13:12:41 by emirzaza          #+#    #+#             */
/*   Updated: 2023/10/10 15:39:38 by emirzaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_cmd_files(t_cmd *cmd, t_lex	**lex, t_lex **temp)
{
	while ((*temp) && (*temp)->token != TOK_PIPE)
	{
		if ((*temp)->token == TOK_IN || (*temp)->token == TOK_OUT)
		{
			if (handle_redir_tokens(cmd, temp))
				return ;
			if ((*temp)->token == TOK_IN)
				(*temp)->next->token = TOK_IN;
			else if ((*temp)->token == TOK_OUT)
				(*temp)->next->token = TOK_OUT;
			(*temp) = (*temp)->next;
		}
		(*temp) = (*temp)->next;
	}
}

int	parse_tokens(t_minishell *mini)
{
	int		cmd_argc;
	t_cmd	*new_cmd;
	t_lex	**temp;
	t_lex	**lex;
	t_lex	*temp1;

	lex = &mini->lex;
	temp1 = mini->lex;
	temp = &temp1;
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
