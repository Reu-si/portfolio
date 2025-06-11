/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildAST_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hreusing <hreusing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 18:44:59 by pbohme            #+#    #+#             */
/*   Updated: 2025/01/06 13:52:24 by hreusing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	type_is_cmd_arg(t_token_type type)
{
	if (type == T_COMMAND || type == T_ARGUMENT || type == T_SINGLE_QUOTE 
		|| type == T_DOUBLE_QUOTE)
		return (1);
	return (0);
}

int	type_is_red_app_her(t_token_type type)
{
	if (type == T_REDIRECT_IN || type == T_REDIRECT_OUT 
		|| type == T_APPEND || type == T_HEREDOC)
		return (1);
	return (0);
}

void	cmd_node(t_AN **current_cmd, t_AN *root, char	*value)
{
	if (!(*current_cmd))
	{
		*current_cmd = create_cmd_node(value);
		add_to_pipeline(root, *current_cmd);
	}
	else 
		add_arg_to_command(*current_cmd, value);
}
