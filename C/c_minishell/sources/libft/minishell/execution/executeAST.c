/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executeAST.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hreusing <hreusing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:08:37 by pbohme            #+#    #+#             */
/*   Updated: 2025/01/20 17:18:52 by hreusing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	handle_single_builtin(t_AN *ast, t_mini *mini)
{
	if (ast->data.pipeline.cmds[0]->type == NODE_COMMAND
		&& ast->data.pipeline.cmd_count == 1
		&& is_builtin(ast->data.pipeline.cmds[0]->data.command.name))
	{
		mini->fork = 0;
		if (ft_setup_redirection(ast->data.pipeline.cmds[0], mini,
				ast->data.pipeline.cmds[0]->data.command.name))
			return (1);
		execute_builtin(ast->data.pipeline.cmds[0]->data.command.name,
			ast->data.pipeline.cmds[0]->data.command.args, &mini->our_env,
			mini);
		dup2(mini->org_stdout, STDOUT_FILENO);
		dup2(mini->org_stdin, STDIN_FILENO);
		close(mini->org_stdout);
		close(mini->org_stdin);
		return (1);
	}
	return (0);
}

void	handle_parent_process(t_AN *ast, pid_t *pids, t_mini *mini)
{
	int	status;
	int	i;

	status = -1;
	i = 0;
	while (i < ast->data.pipeline.cmd_count)
	{
		waitpid(pids[i], &status, 0);
		if (WIFEXITED(status))
		{
			mini->exit_code = WEXITSTATUS(status);
		}
		else if (WIFSIGNALED(status))
		{
			mini->exit_code = WTERMSIG(status) + 128;
		}
		i++;
	}
}

void	execute_single_command(t_AN *node, t_mini *mini, int *prev_pipe_read,
		int *pipe_fd)
{
	create_pipes(prev_pipe_read, pipe_fd, mini);
	mini->fork = 1;
	fork_and_execute_command(node, *prev_pipe_read, pipe_fd, mini);
	exit(mini->exit_code);
}

void	execute_pipeline(t_AN *ast, t_mini *mini)
{
	int		i;
	int		prev_pipe_read;
	int		pipe_fd[2];
	pid_t	*pids;

	ft_init_pipes(&prev_pipe_read, pipe_fd);
	pids = malloc(sizeof(pid_t) * ast->data.pipeline.cmd_count);
	if (!pids)
		handle_pid_error(pids, "malloc");
	i = 0;
	while (i < ast->data.pipeline.cmd_count)
	{
		if (setup_pipeline(i, mini, ast, pipe_fd))
			handle_pid_error(pids, "pipe");
		pids[i] = fork();
		if (pids[i] < 0)
			handle_pid_error(pids, "fork");
		if (pids[i] == 0)
			execute_single_command(ast->data.pipeline.cmds[i], mini,
				&prev_pipe_read, pipe_fd);
		cleanup_pipes(&prev_pipe_read, pipe_fd, mini);
		i++;
	}
	handle_parent_process(ast, pids, mini);
	free(pids);
}

void	execute_ast(t_AN *ast, t_mini *mini)
{
	if (ast->type != NODE_PIPELINE)
	{
		ft_putendl_fd("ROOT node is not a pipe", 2);
		return ;
	}
	mini->cmd_count = ast->data.pipeline.cmd_count;
	if (handle_single_builtin(ast, mini))
		return ;
	execute_pipeline(ast, mini);
	while (wait(NULL) > 0)
		;
}
