/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emirzaza <emirzaza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 19:37:32 by emirzaza          #+#    #+#             */
/*   Updated: 2023/10/06 16:03:05 by emirzaza         ###   ########.fr       */
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
		ft_putstr_fd("\nfiles:\n", 2);
		ft_putstr_fd(mini->file->name, 2);
		ft_putstr_fd("\n", 2);
		ft_putstr_fd(mini->file->next->name, 2);
		ft_putstr_fd("\n\n", 2);
		tmp = tmp->next;
	}
}

void	run_minishell(t_minishell *mini, char *input)
{
	if (!ft_strncmp(input, "exit", ft_strlen(input)) && \
		ft_strlen(input) == 4)
		exit_minishell(input);
	if (!ft_strncmp(input, "env", ft_strlen(input)) && \
		ft_strlen(input) == 3)
		ft_env(mini);
	ft_lookup_input(mini, input);
	//print_commands(mini);
}

int	main(int ac, char **av, char **env)
{
	char				*input;
	t_minishell			mini;

	(void)ac;
	(void)av;
	ft_memset(&mini, 0, sizeof(mini));
	ft_env_init(&mini, env);
	override_ctrl_echo();
	while (1)
	{
		init_interactive_signals();
		input = readline("minishell: ");
		if (ft_strlen(input) > 0)
				add_history(input);
		if (!input)
			exit_minishell(input);
		run_minishell(&mini, input);
		free(input);
	}
	return (0);
}

// < input grep Hello | wc -l > out
// < input grep Hello | awk '{count++} END {print count}' > output
// < input grep Hello | cat -e > out