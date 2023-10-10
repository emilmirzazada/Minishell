/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emirzaza <emirzaza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 19:37:32 by emirzaza          #+#    #+#             */
/*   Updated: 2023/10/10 21:39:51 by emirzaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_commands(t_minishell *mini)
{
	t_cmd	*tmp;
	char	**tmp_args;

	tmp = mini->cmd;
	while (tmp)
	{
		tmp_args = tmp->args;
		while (*tmp_args)
		{
			ft_putstr_fd(*tmp_args, 2);
			ft_putstr_fd("\n", 2);
			tmp_args++;
		}
		ft_putstr_fd("\nfiles \n", 2);
		while (tmp->files)
		{
			if (tmp->files->name)
				ft_putstr_fd(tmp->files->name, 2);
			if (tmp->files->delimeter)
				ft_putstr_fd(tmp->files->delimeter, 2);
			ft_putstr_fd("\n", 2);
			tmp->files = tmp->files->next;
		}
		ft_putstr_fd("\nNew\n", 2);
		tmp = tmp->next;
	}
}

void	run_minishell(t_minishell *mini, char *input)
{
	mini->lex = NULL;
	mini->cmd = NULL;
	ft_lookup_input(mini, input);
	if (!ft_strncmp(input, "exit", ft_strlen(input)) && \
		ft_strlen(input) == 4)
		exit_minishell(input);
	if (!ft_strncmp(input, "env", ft_strlen(input)) && \
		ft_strlen(input) == 3)
		ft_env(mini);
	print_commands(mini);
	//printf("EXIT_CODE = %d\n", execute_commands(mini));
	free(input);
}

int	main(int ac, char **av, char **env)
{
	char				*input;
	t_minishell			mini;
	struct sigaction	sa;

	(void)ac;
	(void)av;
	init_signals(&sa);
	ft_env_init(&mini, env);
	while (1)
	{
		register_signals(&sa);
		input = readline("\e[32m💀💀💀Minishell :\e[0m");
		if (!input)
			exit_minishell(input);
		add_history(input);
		run_minishell(&mini, input);
	}
	return (0);
}

// < input grep Hello | wc -l > out
// < input grep Hello | awk '{count++} END {print count}' > output
// ls > asd | grep input
// shllevel
// > $NAME
// afl++