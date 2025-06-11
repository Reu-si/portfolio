/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbohme <pbohme@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:33:08 by pbohme            #+#    #+#             */
/*   Updated: 2025/01/20 15:33:51 by pbohme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	fork_and_execute_command(t_AN *node, int prev_pipe_read, int pipe_fd[2],
		t_mini *mini)
{
	setup_pipes(prev_pipe_read, pipe_fd[1], mini->is_last_cmd);
	mini->fork = 1;
	if (ft_setup_redirection(node, mini, node->data.command.name))
		exit(mini->exit_code);
	if (node && node->type == NODE_COMMAND)
		exec_cmd(node, mini);
	exit(mini->exit_code);
}

void	execute_command_with_args(t_AN *node, char *path, t_mini *mini)
{
	char	**args;
	int		i;

	args = malloc((node->data.command.arg_count + 2) * sizeof(char *));
	if (!args)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	args[0] = node->data.command.name;
	i = 0;
	while (i < node->data.command.arg_count)
	{
		args[i + 1] = node->data.command.args[i];
		i++;
	}
	args[node->data.command.arg_count + 1] = NULL;
	execve(path, args, mini->our_env);
	perror("minishell: ");
	free(args);
	mini->exit_code = 127;
	exit(mini->exit_code);
}

void	execute_with_path_lookup(t_AN *node, t_mini *mini)
{
	char	*path;

	path = ft_find_path(node->data.command.name, mini);
	if (path)
	{
		execute_command_with_args(node, path, mini);
		free(path);
	}
	else
	{
		mini->exit_code = 127;
		exit(mini->exit_code);
	}
}

void	execute_absolute_path(t_AN *node, t_mini *mini)
{
	char	**args;
	int		i;

	args = malloc((node->data.command.arg_count + 2) * sizeof(char *));
	if (!args)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	args[0] = node->data.command.name;
	i = 0;
	while (i < node->data.command.arg_count)
	{
		args[i + 1] = node->data.command.args[i];
		i++;
	}
	args[node->data.command.arg_count + 1] = NULL;
	execve(node->data.command.name, args, mini->our_env);
	perror("minishell$: ");
	free(args);
	mini->exit_code = 127;
	exit(mini->exit_code);
}

int	exec_cmd(t_AN *node, t_mini *mini)
{
	if (is_builtin(node->data.command.name) && mini->cmd_count > 1)
	{
		execute_builtin(node->data.command.name, node->data.command.args,
			&mini->our_env, mini);
		return (1);
	}
	if (node->data.command.name[0] == '/' || node->data.command.name[0] == '.')
		execute_absolute_path(node, mini);
	else
		execute_with_path_lookup(node, mini);
	return (0);
}
