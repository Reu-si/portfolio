/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_fork.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hreusing <hreusing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 17:53:22 by hreusing          #+#    #+#             */
/*   Updated: 2025/01/20 17:15:38 by hreusing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	ft_open_heredoc_file(t_mini *mini)
{
	int	heredoc_fd;

	heredoc_fd = open("/tmp/heredoc_tmp", O_RDWR | O_CREAT | O_TRUNC, 0600);
	if (heredoc_fd == -1)
	{
		perror("minishell: heredoc file open error");
		mini->exit_code = 1;
	}
	return (heredoc_fd);
}

void	ft_handle_heredoc_child(t_mini *mini, int heredoc_fd, char *delimiter)
{
	ft_setup_heredoc_signals(mini);
	ft_write_heredoc_content(heredoc_fd, delimiter);
	close(heredoc_fd);
	exit(0);
}

void	ft_wait_for_heredoc(pid_t pid, t_mini *mini)
{
	int	status;

	status = 0;
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		mini->exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		mini->exit_code = 128 + WTERMSIG(status);
}

int	ft_fork_heredoc(char *delimiter, t_mini *mini)
{
	int		heredoc_fd;
	pid_t	pid;

	heredoc_fd = ft_open_heredoc_file(mini);
	if (heredoc_fd == -1)
		return (-1);
	pid = fork();
	if (pid == 0)
		ft_handle_heredoc_child(mini, heredoc_fd, delimiter);
	else if (pid > 0)
		ft_wait_for_heredoc(pid, mini);
	else
	{
		perror("fork");
		close(heredoc_fd);
		mini->exit_code = 1;
		return (-1);
	}
	ft_reset_fd(&heredoc_fd, "/tmp/heredoc_tmp", mini);
	return (heredoc_fd);
}
