/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emirzaza <emirzaza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 09:55:02 by emirzaza          #+#    #+#             */
/*   Updated: 2023/09/08 17:27:53 by emirzaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_sigquit()
{
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	handle_sigint(int signum)
{
	if (signum == 3)
	{
		handle_sigquit();
		return ;
	}
	rl_replace_line("", 0);
	ft_putchar_fd('\n', 1);
	rl_on_new_line();
	rl_redisplay();
}

void	exit_minishell(char *input)
{
	printf("Exiting\n");
	if (input)
		free(input);
	exit(1);
}

void	init_signals(struct sigaction *sa)
{
	sa->sa_handler = &handle_sigint;
	sigemptyset(&sa->sa_mask);
	sa->sa_flags = 0;
}

void	register_signals(struct sigaction *sa)
{
	sigaction(SIGINT, sa, NULL);
	sigaction(SIGQUIT, sa, NULL);
}
