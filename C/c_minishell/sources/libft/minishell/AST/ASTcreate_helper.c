/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ASTcreate_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hreusing <hreusing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 12:27:26 by pbohme            #+#    #+#             */
/*   Updated: 2025/01/06 13:52:24 by hreusing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

t_AN	*create_pipeline_node(void)
{
	t_AN	*node;

	node = malloc(sizeof(t_AN));
	if (node == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	node->type = NODE_PIPELINE;
	node->data.pipeline.cmds = NULL;
	node->data.pipeline.cmd_count = 0;
	node->next = NULL;
	return (node);
}

t_AN	*create_cmd_node(char *name)
{
	t_AN	*node;

	node = malloc(sizeof(t_AN));
	if (node == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	node->type = NODE_COMMAND;
	node->data.command.name = ft_strdup(name);
	node->data.command.args = NULL;
	node->data.command.arg_count = 0;
	node->next = NULL;
	return (node);
}

t_AN	*create_red_node(t_token_type type, char *file, t_mini *mini)
{
	t_AN	*node;

	node = malloc(sizeof(t_AN));
	if (node == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	node->type = NODE_REDIRECTION;
	node->data.red.red_type = type;
	node->data.red.file = ft_strdup(file);
	node->data.red.target = NULL;
	node->next = NULL;
	mini->has_redirection++;
	return (node);
}
