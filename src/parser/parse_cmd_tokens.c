/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_tokens.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emirzaza <emirzaza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 12:39:48 by emirzaza          #+#    #+#             */
/*   Updated: 2023/10/15 18:22:58 by emirzaza         ###   ########.fr       */
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

t_cmd	*init_new_command(t_minishell *mini, t_lex *lex, int *cmd_argc)
{
	t_cmd	*new_cmd;
	t_lex	*tmp_lex;

	new_cmd = ft_create_command(mini);
	if (!new_cmd)
		return (NULL);
	tmp_lex = lex;
	ft_bzero(new_cmd, sizeof(new_cmd));
	if (ft_cmd_args_malloc(new_cmd, tmp_lex))
		return (NULL);
	*cmd_argc = 0;
	return (new_cmd);
}
