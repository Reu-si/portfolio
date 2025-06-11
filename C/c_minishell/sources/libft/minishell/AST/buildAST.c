/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildAST.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hreusing <hreusing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 12:18:32 by pbohme            #+#    #+#             */
/*   Updated: 2025/01/20 18:21:30 by hreusing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	red_node(t_token **tokens, t_mini **mini, \
		t_AN **current_cmd, t_AN *root)
{
	t_AN	*current_red;

	current_red = NULL;
	if (!(*tokens)->next || !(*tokens)->next->value)
	{
		ft_putendl_fd("minishell: syntax error near " 
			"unexpected token `newline'", 2);
		(*mini)->exit_code = 2;
		return (2);
	}
	current_red = create_red_node((*tokens)->type, \
		(*tokens)->next->value, *mini);
	if (*current_cmd != NULL)
		add_red_to_cmd(*current_cmd, current_red);
	else
		add_to_pipeline(root, current_red);
	(*tokens) = (*tokens)->next;
	return (0);
}

t_AN	*build_ast(t_token *tokens, t_mini *mini, t_AN *root)
{
	t_AN	*current_cmd;

	root = create_pipeline_node();
	current_cmd = NULL;
	while (tokens)
	{
		if (type_is_cmd_arg(tokens->type))
			cmd_node(&current_cmd, root, tokens->value);
		else if (tokens->type == T_PIPE)
			current_cmd = NULL;
		else if (type_is_red_app_her(tokens->type))
		{
			if (red_node(&tokens, &mini, &current_cmd, root))
				return (NULL);
		}
		else
			return (NULL);
		if (tokens->next == NULL)
			break ;
		tokens = tokens->next;
	}
	return (root);
}
