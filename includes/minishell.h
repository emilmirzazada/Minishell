/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrottger <wrottger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 19:32:07 by emirzaza          #+#    #+#             */
/*   Updated: 2023/10/25 11:28:18 by wrottger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define READLINE_LIBRARY

# include <stdbool.h>
# include <errno.h>
# include <termios.h>
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

typedef struct s_sdata
{
	char		l_char;
	char		*l_arg;
	bool		is_text;
}				t_sdata;

typedef struct s_split
{
	char			*arg;
	bool			is_text;
	struct s_split	*next;
}				t_split;

typedef struct s_minishell
{
	char			*input;
	t_env			*env;
	char			**env_arr;
	t_stdio			std_io;
	t_cmd			*cmd;
	t_lex			*lex;
	t_split			*split;
	int				*pids;
}				t_minishell;

//expansion
char	*expand(t_minishell *mini);
int		expansion_end_check(char *s, char *check);
char	*place_value(char *temp, char *value, char *s, int *t);
void	place_rest_of_string(char *s, char *temp, int *i, int *t);
char	*get_name(char *s, int i);
char	*expand_dollar_special(char c, int *i);

// builtins
int		ft_echo (t_cmd *cmd);
t_env	*ft_env_init( char **env);
t_env	*ft_set_raw_env(char *env_str);
t_env	*ft_setenv(char *key, char *value);
int		ft_env(t_minishell *mini);
char	*find_env(t_env *lst, char *key);
void	set_env_array(t_minishell *mini);
void	ft_envadd_back(t_env **lst, t_env *new);
int		ft_cd(t_minishell *mini, t_cmd *cmd);
int		ft_pwd(void);
int		ft_export(t_minishell *mini, t_cmd *cmd);
void	export_echo_sorted(t_minishell *mini);
bool	validate_arg(char *str);
int		ft_unset(t_minishell *mini, t_cmd *cmd);
int		ft_exit(t_minishell *mini, t_cmd *cmd);

// cleaner
void	perror_exit(char *str, t_minishell *mini, int exit_code);
void	free_mini(t_minishell *mini);
void	clean_exit(t_minishell *mini, int exit_code);

// executor
int		execute_commands(t_minishell *mini);
int		*create_pipes(int pipe_count);
int		clean_pipes(int *pipes, int size);
char	*get_executable_path(
			t_minishell *mini,
			t_cmd cmd,
			const char	*path_env);
int		execute_builtin(t_minishell *mini);
int		loop_commands(t_minishell *mini, int *pipe_fds, int command_count);
int		execute_program(t_minishell *mini);
int		is_builtin(char *name);
int		execute_command(t_minishell *mini);
void	free_command(t_cmd *cmd);
int		execute_single_builtin(t_minishell *mini);
void	create_heredocs(t_minishell *mini);
void	save_stdio(t_stdio std_io);
void	load_stdio(t_stdio std_io);
int		configure_pipes(t_minishell *mini, int *pipe_fds, int j);
int		here_doc(t_minishell *mini, char *delimiter, char *name);


// parser
int		parse_tokens(t_minishell *mini);
int		handle_redir_tokens(t_cmd *cmd, t_lex **lex);
int		handle_heredoc_token(t_cmd *cmd, t_lex **temp);
bool	init_new_command(t_minishell *mini, t_cmd **newcmd, t_lex *lex, int *cmd_argc);
void	create_file(t_cmd *cmd, t_token token, char *name);

// signals
void	init_interactive_signals(void);
void	init_non_interactive_signals(void);
void	override_ctrl_echo(void);
void	exit_minishell(char *input);

// splitter
bool	ft_input_split(t_minishell *mini, char *s);
char	*handle_redir_symbols(char *s);
bool	ft_isspace(int c);
int		skip_quotes(char *s, int i);
int		check_quotes(char *s);
char	*split_quotes(char *s, int *i, char q);
char	*split_pipe(char *s, int *i, char c);
char	*split_word(char *s, int *i);
int		skip_spaces(char *s);
void	ft_split_addback(t_split **lst, t_split *new);
void	remove_split(t_split **lst, char *key);

// tokenizer
int	ft_lookup_input(t_minishell *mini);

#endif