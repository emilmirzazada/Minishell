/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emirzaza <emirzaza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 19:32:07 by emirzaza          #+#    #+#             */
/*   Updated: 2023/10/05 17:23:17 by emirzaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define READLINE_LIBRARY

# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <sys/wait.h>
#include <sys/stat.h>
# include "libft.h"
# include "../readline/include/history.h"
# include "../readline/include/readline.h"
# include "../readline/include/rlstdc.h"

# define STDIN 0
# define STDOUT 1
# define STDERR 2

typedef enum s_token
{
	TOK_WORD = 'W',
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
	char			*path;
	char			**args;
	struct s_cmd	*next;
}				t_cmd;

typedef struct s_minishell
{
	struct s_env	*env;
	char			**env_arr;
	char			**args;
	t_cmd			*cmd;
	t_file			*file;
	t_lex			*lex;
}				t_minishell;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}				t_env;

// builtins
void	ft_env_init(t_minishell *mini, char **env);
int		ft_env(t_minishell *cmd);
char	*find_env(t_env *lst, char *key);
static	void	set_env_array(t_minishell *mini);

// executor
int		execute_commands(t_minishell *mini);
int		*create_pipes(int pipe_count);
int		clean_pipes(int *pipes, int size);
char	*get_executable_path(t_cmd cmd, char *pwd, char	*path_env);

// parser
int		parse_tokens(t_minishell *mini);
int		handle_redir_tokens(t_minishell *mini, t_lex **lex);
int		handle_word_tokens(t_minishell *mini, t_lex **lex);

// signals
void	init_signals(struct sigaction *sa);
void	register_signals(struct sigaction *sa);
void	exit_minishell(char *input);

// splitter
char	**ft_input_split(char *s);
bool	ft_isspace(int c);
bool	ft_mode_equal(char *m1, char *m2, int len);
bool	ft_mode_diff(char *m1, char *m2, int len);
void	ft_shift_special_chr(char **s, char *mode);
char	*ft_check_special_chr(int c1, int c2, int c0);
char	*ft_removechr(char	*str, char chr);
void	free_set_null(void **ptr);

// tokenizer
void	ft_lookup_input(t_minishell *mini, char *input);

#endif