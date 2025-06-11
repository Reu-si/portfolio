/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbohme <pbohme@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 18:41:05 by pbohme            #+#    #+#             */
/*   Updated: 2025/01/20 13:23:13 by pbohme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	free_standalone_redirection(t_AN *node)
{
	if (!node || node->type != NODE_REDIRECTION)
		return ;
	free(node->data.red.file);
	free_ast(node->data.red.target);
}

void	free_redirection_nodes(t_AN *node)
{
	t_AN	*current;
	t_AN	*next;

	if (!node || node->type != NODE_COMMAND)
		return ;
	current = node->next;
	while (current && current->type == NODE_REDIRECTION)
	{
		next = current->next;
		free(current->data.red.file);
		current->data.red.file = NULL;
		free(current);
		current = next;
	}
	node->next = NULL;
}

void	free_command_node(t_AN *node)
{
	int	i;

	if (!node || node->type != NODE_COMMAND)
		return ;
	free(node->data.command.name);
	node->data.command.name = NULL;
	i = 0;
	while (i < node->data.command.arg_count && node->data.command.arg_count)
	{
		free(node->data.command.args[i]);
		node->data.command.args[i] = NULL;
		i++;
	}
	free(node->data.command.args);
	node->data.command.args = NULL;
}

void	free_ast(t_AN *node)
{
	int	i;

	if (node == NULL)
		return ;
	if (node->type == NODE_PIPELINE)
	{
		i = 0;
		while (i < node->data.pipeline.cmd_count && \
				node->data.pipeline.cmd_count)
		{
			free_ast(node->data.pipeline.cmds[i]);
			node->data.pipeline.cmds[i] = NULL;
			i++;
		}
		free(node->data.pipeline.cmds);
		node->data.pipeline.cmds = NULL;
	}
	else if (node->type == NODE_COMMAND)
		free_command_node(node);
	else if (node->type == NODE_REDIRECTION)
		free_standalone_redirection(node);
	free_redirection_nodes(node);
	free(node);
}

void	free_mini(t_mini *mini)
{
	int	i;

	if (mini->our_env)
	{
		i = 0;
		while (mini->our_env[i] != NULL)
		{
			free(mini->our_env[i]);
			i++;
		}
		free(mini->our_env);
	}
	free(mini);
}
