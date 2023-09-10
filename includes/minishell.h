/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emirzaza <emirzaza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 19:32:07 by emirzaza          #+#    #+#             */
/*   Updated: 2023/09/10 11:28:35 by emirzaza         ###   ########.fr       */
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

typedef struct	s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}				t_env;

//signals
void	init_signals(struct sigaction *sa);
void	register_signals(struct sigaction *sa);
void	exit_minishell(char *input);

//env
void	env_init(t_minishell *mini, char **env);
int		ft_env(t_minishell *cmd);

// parser
bool	ft_isspace(int c);
bool	ft_mode_equal(char *m1, char *m2, int len);
bool	ft_mode_diff(char *m1, char *m2, int len);
void	ft_shift_special_chr(char **s, char *mode);
char	*ft_check_special_chr(int c1, int c2, int c0);

#endif