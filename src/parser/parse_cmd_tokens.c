/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_tokens.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emirzaza <emirzaza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 12:39:48 by emirzaza          #+#    #+#             */
/*   Updated: 2023/10/24 17:14:40 by emirzaza         ###   ########.fr       */
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
	*new_cmd = (t_cmd){0};
	ft_command_addback(&(mini->cmd), new_cmd);
	return (new_cmd);
}

int	ft_cmd_args_malloc(t_cmd *cmd, t_lex *lex)
{
	t_lex	*temp;
	int		argc;

	temp = lex;
	argc = 0;
	while (lex && lex->token != TOK_ARG)
		lex = lex->next;
	while (lex && lex->token != TOK_PIPE)
	{
		if (lex->token == TOK_ARG)
			argc++;
		lex = lex->next;
	}
	cmd->args = ft_calloc(sizeof(char **), (argc + 2));
	if (!(cmd->args))
		return (1);
	return (0);
}

bool	init_new_command(t_minishell *mini, t_cmd **cmd, t_lex *lex, int *argc)
{
	t_lex	*tmp_lex;

	if (lex && lex->token == TOK_PIPE && lex->next
		&& lex->next->token == TOK_PIPE)
		return (\
		printf("Minishell: syntax error near unexpected token `|'\n"), false);
	*cmd = ft_create_command(mini);
	if (!cmd)
		return (false);
	tmp_lex = lex;
	if (ft_cmd_args_malloc(*cmd, tmp_lex))
		return (false);
	*argc = 0;
	return (true);
}
