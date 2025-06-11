/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_r_a_h_p.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hreusing <hreusing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 17:20:56 by pbohme            #+#    #+#             */
/*   Updated: 2025/01/20 18:17:50 by hreusing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	ft_tokenize_pipe(t_token **head, t_token **tail)
{
	t_token	*pipe_token;

	pipe_token = create_token("|", T_PIPE);
	if (!pipe_token)
		return (0);
	append_to_list(head, tail, pipe_token);
	return (1);
}

int	ft_tokenize_red_app_her(t_token **head, t_token **tail, const char **input)
{
	t_token	*new_token;

	new_token = NULL;
	if ((*input)[2] == '<' || (*input)[2] == '>' 
			|| (*input)[2] == '|' || (*input)[2] == '\0')
		return (printf("minishell: syntax error near unexpected token\n"), 0);
	if ((*input)[0] == '<' && (*input)[1] == '<')
		new_token = create_token("<<", T_HEREDOC);
	else if ((*input)[0] == '>' && (*input)[1] == '>')
		new_token = create_token(">>", T_APPEND);
	else if ((*input)[0] == '<')
		new_token = create_token("<", T_REDIRECT_IN);
	else if ((*input)[0] == '>')
		new_token = create_token(">", T_REDIRECT_OUT);
	if (((*input)[0] == '<' && (*input)[1] == '<') 
		|| ((*input)[0] == '>' && (*input)[1] == '>'))
		*input += 2;
	else if ((*input)[0] == '<' || (*input)[0] == '>')
		(*input)++;
	if (!new_token)
		return (0);
	append_to_list(head, tail, new_token);
	return (1);
}
