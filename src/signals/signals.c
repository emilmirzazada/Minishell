/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emirzaza <emirzaza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 09:55:02 by emirzaza          #+#    #+#             */
/*   Updated: 2023/10/19 13:39:18 by emirzaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	interactive_signal_handler(int sign)
{
	if (sign == SIGINT)
	{
		g_exit_code = 128 + sign;
		rl_replace_line("", 0);
		write(STDIN_FILENO, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
	}
}

static void	non_interactive_signal_handler(int sign)
{
	if (sign == SIGINT)
	{
		g_exit_code = sign;
		rl_replace_line("", 0);
	}
	else if (sign == SIGQUIT)
	{
		g_exit_code = sign;
		ft_putstr_fd("Quit: ", STDERR_FILENO);
		ft_putnbr_fd(sign, STDERR_FILENO);
		write(STDIN_FILENO, "\n", 1);
		rl_replace_line("", 0);
	}
}

void	init_interactive_signals(void)
{
	signal(SIGINT, interactive_signal_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	init_non_interactive_signals(void)
{
	signal(SIGINT, &non_interactive_signal_handler);
	signal(SIGQUIT, &non_interactive_signal_handler);
}

void	override_ctrl_echo(void)
{
	struct termios	term;

	if (isatty(STDIN_FILENO))
	{
		tcgetattr(STDIN_FILENO, &term);
		term.c_lflag = term.c_lflag & ~ECHOCTL;
		tcsetattr(STDIN_FILENO, TCSANOW, &term);
	}
	else if (isatty(STDOUT_FILENO))
	{
		tcgetattr(STDOUT_FILENO, &term);
		term.c_lflag = term.c_lflag & ~ECHOCTL;
		tcsetattr(STDOUT_FILENO, TCSANOW, &term);
	}
	else if (isatty(STDERR_FILENO))
	{
		tcgetattr(STDERR_FILENO, &term);
		term.c_lflag = term.c_lflag & ~ECHOCTL;
		tcsetattr(STDERR_FILENO, TCSANOW, &term);
	}
}
