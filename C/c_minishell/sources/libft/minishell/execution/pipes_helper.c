/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hreusing <hreusing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:28:00 by pbohme            #+#    #+#             */
/*   Updated: 2025/01/20 12:40:16 by hreusing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	create_pipes(int *prev_pipe_read, int *pipe_fd, t_mini *mini)
{
	if (*prev_pipe_read != -1)
	{
		if (dup2(*prev_pipe_read, STDIN_FILENO) == -1) 
		{
			perror("dup2");
			exit(EXIT_FAILURE);
		}
		close(*prev_pipe_read);
	}
	if (!mini->is_last_cmd)
	{
		if (dup2(pipe_fd[1], STDOUT_FILENO) == -1) 
		{
			perror("dup2 (pipe_fd[1] to STDOUT)");
			exit(EXIT_FAILURE);
		}
		close(pipe_fd[1]);
	}
	if (pipe_fd[0] != -1)
		close(pipe_fd[0]);
}

void	setup_pipes(int input_fd, int output_fd, int is_last_cmd)
{
	if (input_fd != STDIN_FILENO && input_fd != -1)
	{
		dup2(input_fd, STDIN_FILENO);
		close(input_fd);
	}
	if (!is_last_cmd)
	{
		dup2(output_fd, STDOUT_FILENO);
		close(output_fd);
	}
}

void	cleanup_pipes(int *prev_pipe_read, int *pipe_fd, t_mini *mini)
{
	if (*prev_pipe_read != -1)
		close(*prev_pipe_read);
	if (!mini->is_last_cmd)
		close(pipe_fd[1]);
	*prev_pipe_read = pipe_fd[0];
}

void	handle_pid_error(pid_t *pids, char *error)
{
	perror(error);
	free(pids);
	exit(EXIT_FAILURE);
}

int	setup_pipeline(int i, t_mini *mini, t_AN *ast, int *pipe_fd)
{
	mini->current_cmd = i;
	mini->is_last_cmd = (i == ast->data.pipeline.cmd_count - 1);
	if (!mini->is_last_cmd && pipe(pipe_fd) == -1)
		return (1);
	if (ast->data.pipeline.cmds[i]->type == NODE_REDIRECTION)
		ft_create_file(ast->data.pipeline.cmds[i], mini);
	return (0);
}
