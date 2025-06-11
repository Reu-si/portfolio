/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hreusing <hreusing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 17:53:22 by hreusing          #+#    #+#             */
/*   Updated: 2025/01/20 18:21:11 by hreusing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	ft_reset_fd(int	*heredoc_fd, const char *heredoc_file, t_mini *mini)
{
	if (*heredoc_fd != -1)
		close(*heredoc_fd);
	*heredoc_fd = open(heredoc_file, O_RDONLY);
	if (*heredoc_fd == -1)
	{
		perror("open");
		mini->exit_code = 1;
		exit (mini->exit_code);
	}
}

void	signal_heredoc_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_signum = SIGINT;
		if (!rl_done)
		{
			write(STDOUT_FILENO, "\n", 1);
		}
		rl_done = 1;
	}
}

void	ft_setup_heredoc_signals(t_mini *mini)
{
	struct sigaction	sa;

	sa.sa_handler = signal_heredoc_handler;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGINT, &sa, NULL) == -1)
	{
		perror("sigaction");
		exit(EXIT_FAILURE);
	}
	signal(SIGQUIT, SIG_IGN);
	ft_reset_term_attr(mini);
}

void	ft_write_heredoc_content(int fd, char *delimiter)
{
	char	*line;
	size_t	len;

	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			ft_printf_stderr("minishell: warning: here-document delimited " \
				"by end-of-file (wanted `", delimiter, "')");
			break ;
		}
		len = ft_strlen(line);
		if (ft_strcmp(line, delimiter) == 0)
			break ;
		write(fd, line, len);
		write(fd, "\n", 1);
		free(line);
	}
	free(line);
}

void	ft_handle_heredoc(char *delimiter, t_mini *mini)
{
	int		fd;

	fd = open("/tmp/heredoc_tmp", O_RDWR | O_CREAT | O_TRUNC, 0600);
	if (fd == -1)
	{
		perror("minishell: heredoc file open error");
		mini->exit_code = 1;
		return ;
	}
	ft_setup_heredoc_signals(mini);
	ft_write_heredoc_content(fd, delimiter);
	ft_handle_signals_interactive();
	ft_reset_fd(&fd, "/tmp/heredoc_tmp", mini);
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("dup2");
		close(fd);
		unlink("/tmp/heredoc_tmp");
		mini->exit_code = 1;
		return ;
	}
	close(fd);
	unlink("/tmp/heredoc_tmp");
	ft_reset_term_attr(mini);
}
