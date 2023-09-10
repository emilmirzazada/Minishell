/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emirzaza <emirzaza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 19:37:32 by emirzaza          #+#    #+#             */
/*   Updated: 2023/09/08 18:48:14 by emirzaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	char				*input;
	t_minishell			mini;
	struct sigaction	sa;

	init_signals(&sa);
	env_init(&mini, env);
	while (1)
	{
		register_signals(&sa);
		input = readline("minihell: ");
		if (!input)
			exit_minishell(input);
		if (!ft_strncmp(input, "exit", ft_strlen(input)) && \
			ft_strlen(input) == 4)
			exit_minishell(input);
		if (!ft_strncmp(input, "env", ft_strlen(input)) && \
			ft_strlen(input) == 3)
			ft_env(&mini);
		free(input);
	}
	return (0);
}
