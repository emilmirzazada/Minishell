/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emirzaza <emirzaza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 19:32:07 by emirzaza          #+#    #+#             */
/*   Updated: 2023/10/06 12:51:10 by emirzaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define READLINE_LIBRARY

#include <stdbool.h>
#include <errno.h>
#include <termios.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "libft.h"
# include "../readline/include/history.h"
# include "../readline/include/readline.h"
# include "../readline/include/rlstdc.h"

# define STDIN 0
# define STDOUT 1
# define STDERR 2

int		g_exit_code;

typedef enum s_token
{
	TOK_ARG = 'A',
	TOK_PIPE = '|',
	TOK_IN = '<',
	TOK_OUT = '>',
	TOK_HERE_DOC = 'H',
}			t_token;

typedef struct s_lex
{
	t_token			token;
	char			*value;
	struct s_lex	*next;
}				t_lex;

typedef struct s_file
{
	char			*name;
	t_token			token;
	char			*delimeter;
	struct s_file	*next;
}				t_file;

typedef struct s_cmd
{
	char			*cmd;
	int				exit_code;
	char			*path;
	char			**args;
	struct s_cmd	*next;
}				t_cmd;

typedef struct s_minishell
{
	struct s_env	*env;
	char			**env_arr;
	t_cmd			*cmd;
	t_file			*file;
	t_lex			*lex;
}				t_minishell;

typedef struct	s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}				t_env;

//builtins
void	echo (t_cmd *cmd);

//expansion
char	*expand(t_minishell *mini, char *s);
int		expansion_end_check(char *s, char *check);
char	*place_value(char *temp, char *value, char *s);
void	place_rest_of_string(char *s, char *temp, int *i, int *t);
char	*get_name(char *s, int i);
char	*last_command_exit_code(char c, int *i);

//signals
void	init_interactive_signals();
void	init_non_interactive_signals(void);
void	override_ctrl_echo(void);
void	exit_minishell(char *input);

//env
void	ft_env_init(t_minishell *mini, char **env);
int		ft_env(t_minishell *cmd);

//lexer
void	ft_lookup_input(t_minishell *mini, char *input);

//parser
int		parse_tokens(t_minishell *mini);
int 	handle_redir_tokens(t_minishell *mini, t_lex **lex);
int		handle_word_tokens(t_minishell *mini, t_lex **lex);

// splitter
char	**ft_input_split(char *s);
char	*handle_redir_symbols(char *s);
bool	ft_isspace(int c);
bool	ft_mode_equal(char *m1, char *m2, int len);
bool	ft_mode_diff(char *m1, char *m2, int len);
void	ft_shift_special_chr(char **s, char *mode);
char	*ft_check_special_chr(int c1, int c2, int c0);
char	*ft_removechr(char	*str, char chr);
void	free_set_null(void **ptr);

#endif