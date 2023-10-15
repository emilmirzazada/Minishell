/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emirzaza <emirzaza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 19:32:07 by emirzaza          #+#    #+#             */
/*   Updated: 2023/10/15 14:40:45 by emirzaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define READLINE_LIBRARY

# include <stdbool.h>
#include <errno.h>
#include <termios.h>
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "libft.h"
# include "../readline/include/history.h"
# include "../readline/include/readline.h"
# include "../readline/include/rlstdc.h"

# define STDIN 0
# define STDOUT 1
# define STDERR 2

int		g_exit_code;

typedef struct s_stdio
{
	int	stdin;
	int	stdout;
}				t_stdio;

typedef enum s_token
{
	TOK_ARG = 'G',
	TOK_PIPE = '|',
	TOK_IN = '<',
	TOK_OUT = '>',
	TOK_HERE_DOC = 'H',
	TOK_APPEND = 'A'
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
	int				fds;
	t_token			token;
	char			*delimeter;
	struct s_file	*next;
}				t_file;

typedef struct s_cmd
{
	char			*name;
	int				exit_code;
	t_file			*files;
	char			*path;
	char			**args;
	struct s_cmd	*next;
}				t_cmd;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}				t_env;

typedef struct s_minishell
{
	t_env			*env;
	char			**env_arr;
	t_stdio			std_io;
	t_cmd			*cmd;
	t_lex			*lex;
}				t_minishell;

//expansion
char	*expand(t_minishell *mini, char *s);
int		expansion_end_check(char *s, char *check);
char	*place_value(char *temp, char *value, char *s);
void	place_rest_of_string(char *s, char *temp, int *i, int *t);
char	*get_name(char *s, int i);
char	*last_command_exit_code(char c, int *i);

// builtins
int		echo (t_cmd *cmd);
void	ft_env_init(t_minishell *mini, char **env);
int		ft_env(t_minishell *mini);
char	*find_env(t_env *lst, char *key);
void	set_env_array(t_minishell *mini);
int		ft_cd(t_minishell *mini, t_cmd *cmd);
int		ft_pwd(void);

// executor
int		execute_commands(t_minishell *mini);
int		*create_pipes(int pipe_count);
int		clean_pipes(int *pipes, int size);
char	*get_executable_path(t_cmd cmd, const char *pwd, const char	*path_env);
int		execute_builtin(t_minishell *mini);
int		execute_program(t_minishell *mini);
int		is_builtin(char *name);
void	save_stdio(t_stdio std_io);
void	load_stdio(t_stdio std_io);
int		configure_pipes(t_minishell *mini, int *pipe_fds, int j);


// parser
int		parse_tokens(t_minishell *mini);
int		handle_redir_tokens(t_cmd *cmd, t_lex **lex);
int		handle_heredoc_token(t_cmd *cmd, t_lex **temp);
t_cmd	*init_new_command(t_minishell *mini, t_lex *lex, int *cmd_argc);
void	create_file(t_cmd *cmd, t_token token, char *name);

// signals
void	init_interactive_signals();
void	init_non_interactive_signals(void);
void	override_ctrl_echo(void);
void	exit_minishell(char *input);

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

// tokenizer
int	ft_lookup_input(t_minishell *mini, char *input);

#endif