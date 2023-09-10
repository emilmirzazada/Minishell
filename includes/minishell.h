/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emirzaza <emirzaza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 19:32:07 by emirzaza          #+#    #+#             */
/*   Updated: 2023/09/08 18:48:06 by emirzaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define READLINE_LIBRARY

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include "../libft/libft.h"
# include "../readline/include/history.h"
# include "../readline/include/readline.h"
# include "../readline/include/rlstdc.h"

# define STDIN 0
# define STDOUT 1
# define STDERR 2

typedef struct s_minishell
{
	struct s_env	*env;
	char			**args;
}				t_minishell;


void	init_signals(struct sigaction *sa);
void	register_signals(struct sigaction *sa);
void	exit_minishell(char *input);

typedef struct	s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}				t_env;


void	env_init(t_minishell *mini, char **env);
int		ft_env(t_minishell *cmd);

#endif