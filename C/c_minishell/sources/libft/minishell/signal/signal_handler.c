/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hreusing <hreusing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 14:17:44 by hreusing          #+#    #+#             */
/*   Updated: 2024/11/29 12:35:35 by hreusing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

volatile sig_atomic_t	g_signum = 0;

void	ft_reset_line(int sig)
{
	if (sig == SIGINT)
	{
		g_signum = SIGINT;
		rl_replace_line("", 0);
		rl_on_new_line();
		write(STDOUT_FILENO, "\n", 1);
		rl_redisplay();
	}
}

void	ft_display_new_line(int sig)
{
	(void)sig;
	if (sig == SIGQUIT)
	{
		g_signum = SIGQUIT;
		ft_putendl_fd("Quit (core dumped)", 2);
	}
	if (sig == SIGINT)
	{
		g_signum = SIGINT;
		write(STDOUT_FILENO, "\n", 1);
	}
	rl_on_new_line();
}

void	ft_handle_signals_non_interactive(void)
{
	signal(SIGINT, ft_display_new_line);
	signal(SIGQUIT, ft_display_new_line);
}

void	ft_handle_signals_interactive(void)
{
	struct sigaction	sa;

	sa.sa_handler = ft_reset_line;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if (sigaction(SIGINT, &sa, NULL) == -1)
	{
		perror("sigaction");
		exit(EXIT_FAILURE);
	}
	signal(SIGQUIT, SIG_IGN);
}

void	ft_signal_exitcode(t_mini *mini)
{
	if (g_signum == SIGINT)
	{
		mini->exit_code = 130;
	}
	if (g_signum == SIGQUIT)
	{
		mini->exit_code = 131;
	}
	g_signum = 0;
}
