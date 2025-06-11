/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hreusing <hreusing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 16:46:01 by hreusing          #+#    #+#             */
/*   Updated: 2025/01/20 16:48:03 by hreusing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	ft_open_file(char *file, int open_type, int *err)
{
	int	fd;

	fd = -2;
	if (open_type == 0)
	{
		fd = open(file, O_RDONLY);
		*err = errno;
	}
	else if (open_type == 1 || open_type == 2)
	{
		if (open_type == 1)
			fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (open_type == 2)
			fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		*err = errno;
	}
	return (fd);
}

void	handle_file_error(int err, char *file, t_mini *mini)
{
	if (err == 2)
		ft_printf_stderr("minishell: ", file, ": No such file or directory");
	else if (err == 13)
		ft_printf_stderr("minishell: ", file, ": Permission denied");
	mini->exit_code = 1;
}

int	ft_handle_fds(char *file, int open_type, t_mini *mini, char *cmd)
{
	int	fd;
	int	err;

	fd = -1;
	if (open_type == 0)
	{
		fd = ft_open_file(file, open_type, &err);
		if (ft_strcmp(cmd, "echo") != 0)
			dup2(fd, STDIN_FILENO);
		close(fd);
	}
	else if (open_type == 1 || open_type == 2)
	{
		fd = ft_open_file(file, open_type, &err);
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	if (fd == -1)
	{
		handle_file_error(err, file, mini);
		if (mini->fork == 1)
			exit (mini->exit_code);
		return (1);
	}
	return (0);
}

int	ft_setup_redirection(t_AN *node, t_mini *mini, char *cmd)
{
	t_AN	*current;
	int		status;
	char	*file;

	current = node;
	status = 0;
	if (!current->next || !current->next->data.red.file)
		return (0);
	while (current && current->next)
	{
		file = current->next->data.red.file;
		if (current->next->data.red.red_type == T_HEREDOC)
			ft_handle_heredoc(file, mini);
		else if (current->next->data.red.red_type == T_REDIRECT_IN)
			status = ft_handle_fds(file, 0, mini, cmd);
		else if (current->next->data.red.red_type == T_REDIRECT_OUT)
			status = ft_handle_fds(file, 1, mini, cmd);
		else if (current->next->data.red.red_type == T_APPEND)
			status = ft_handle_fds(file, 2, mini, cmd);
		if (status == 1)
			return (1);
		else if (current->next)
			current = current->next;
	}
	return (0);
}

int	ft_create_file(t_AN *node, t_mini *mini)
{
	t_AN	*current;
	int		fd;
	int		err;

	current = node;
	fd = -2;
	err = -1;
	if (current->data.red.red_type == T_HEREDOC)
		fd = ft_fork_heredoc(current->data.red.file, mini);
	else if (current->data.red.red_type == T_REDIRECT_IN)
		fd = ft_open_file(current->data.red.file, 0, &err);
	else if (current->data.red.red_type == T_REDIRECT_OUT)
		fd = ft_open_file(current->data.red.file, 1, &err);
	else if (current->data.red.red_type == T_APPEND)
		fd = ft_open_file(current->data.red.file, 2, &err);
	if (fd == -1)
	{
		handle_file_error(err, current->data.red.file, mini);
		return (1);
	}
	return (0);
}
