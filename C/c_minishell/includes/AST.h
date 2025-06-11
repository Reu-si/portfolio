/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AST.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hreusing <hreusing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 12:07:23 by pbohme            #+#    #+#             */
/*   Updated: 2025/01/06 13:52:24 by hreusing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

// # include "minishell.h"

# define INITIAL_CAPACITY 4
# define GROWTH_FACTOR 2

typedef enum e_token_type
{
	T_COMMAND,
	T_ARGUMENT,
	T_PIPE,
	T_REDIRECT_IN,
	T_REDIRECT_OUT,
	T_APPEND,
	T_HEREDOC,
	T_SINGLE_QUOTE,
	T_DOUBLE_QUOTE,
	T_END
}								t_token_type;

typedef enum e_NodeType
{
	NODE_PIPELINE,
	NODE_COMMAND,
	NODE_REDIRECTION
}								t_NodeType;

typedef struct s_ASTNode
{
	t_NodeType					type;
	int							has_red;
	union						u_data
	{
		struct					s_pipeline
		{
			struct s_ASTNode	**cmds;
			int					cmd_count;
		} pipeline;
		struct					s_command
		{
			char				*name;
			char				**args;
			int					arg_count;
		} command;
		struct					s_red
		{
			t_token_type		red_type;
			char				*file;
			struct s_ASTNode	*target;
		} red;
	} data;
	struct s_ASTNode			*next;
}								t_AN;

#endif
