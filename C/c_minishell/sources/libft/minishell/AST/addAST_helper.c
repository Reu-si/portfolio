/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addAST_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbohme <pbohme@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 12:32:11 by pbohme            #+#    #+#             */
/*   Updated: 2025/01/17 13:55:35 by pbohme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	init_pipeline(t_AN **pipeline)
{
	(*pipeline)->data.pipeline.cmds = malloc \
	(INITIAL_CAPACITY * sizeof(t_AN));
	if (!(*pipeline)->data.pipeline.cmds)
	{
		perror ("malloc");
		exit (EXIT_FAILURE);
	}
	(*pipeline)->data.pipeline.cmd_count = 0;
}

void	add_to_pipeline(t_AN *pipeline, t_AN *node)
{
	int		i;
	size_t	new_capacity;
	t_AN	**new_cmds;

	new_cmds = NULL;
	i = 0;
	if (pipeline->data.pipeline.cmd_count == 0)
		init_pipeline(&pipeline);
	else if (pipeline->data.pipeline.cmd_count >= INITIAL_CAPACITY 
		&& pipeline->data.pipeline.cmd_count % INITIAL_CAPACITY == 0)
	{
		new_capacity = pipeline->data.pipeline.cmd_count * GROWTH_FACTOR;
		new_cmds = malloc(new_capacity * sizeof(t_AN *));
		while (i < pipeline->data.pipeline.cmd_count)
		{
			new_cmds[i] = pipeline->data.pipeline.cmds[i];
			i++;
		}
		free(pipeline->data.pipeline.cmds);
		pipeline->data.pipeline.cmds = new_cmds;
	}
	pipeline->data.pipeline.cmds[pipeline->data.pipeline.cmd_count] = node;
	pipeline->data.pipeline.cmd_count++;
}

void	resize_array(t_AN **command)
{
	size_t	new_capacity;
	char	**new_args;
	int		i;

	new_capacity = (*command)->data.command.arg_count * GROWTH_FACTOR;
	new_args = ft_calloc(new_capacity, sizeof(char *));
	if (!new_args)
	{
		perror ("malloc");
		exit (EXIT_FAILURE);
	}
	i = 0;
	while (i < (*command)->data.command.arg_count)
	{
		new_args[i] = (*command)->data.command.args[i];
		i++;
	}
	free((*command)->data.command.args);
	(*command)->data.command.args = new_args;
}

void	add_arg_to_command(t_AN *command, char *arg)
{
	char	*dup_arg;

	if (command->data.command.arg_count == 0)
	{
		command->data.command.args = ft_calloc(INITIAL_CAPACITY + 1,
				sizeof(char *));
		if (!command->data.command.args)
		{
			perror("ft_calloc");
			exit(EXIT_FAILURE);
		}
	}
	if (command->data.command.arg_count >= INITIAL_CAPACITY
		&& command->data.command.arg_count % INITIAL_CAPACITY == 0)
		resize_array(&command);
	dup_arg = ft_strndup(arg, ft_strlen(arg));
	if (!dup_arg)
	{
		perror("ft_strdup");
		exit(EXIT_FAILURE);
	}
	command->data.command.args[command->data.command.arg_count] = dup_arg;
	command->data.command.arg_count++;
	if (command->data.command.arg_count < INITIAL_CAPACITY)
		command->data.command.args[command->data.command.arg_count] = NULL;
}
//if (cmd == NULL)
//	{
//ft_putendl_fd("Error: Trying to add redirection to a "
//	"non-command node", 2);
// 	return ;
//	}

void	add_red_to_cmd(t_AN *cmd, t_AN *redirection)
{
	t_AN	*last;

	if (cmd == NULL)
		return ;
	redirection->data.red.target = cmd;
	if (!cmd->next)
	{
		cmd->next = redirection;
	}
	else
	{
		last = cmd->next;
		while (last->next && last->next->type == NODE_REDIRECTION)
		{
			last = last->next;
		}
		redirection->next = last->next;
		last->next = redirection;
	}
}
