/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbohme <pbohme@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 14:25:29 by pbohme            #+#    #+#             */
/*   Updated: 2025/01/17 14:20:08 by pbohme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	is_whitespace(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

void	skip_whitespace(const char **input)
{
	while (is_whitespace(**input))
		(*input)++;
}

void	append_to_list(t_token **head, t_token **tail, t_token *new)
{
	if (!new)
		return ;
	if (!(*head))
	{
		*head = new;
		*tail = *head;
	}
	else
	{
		(*tail)->next = new;
		new->prev = *tail;
		*tail = new;
	}
}

t_token	*create_token(const char *value, t_token_type type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->value = ft_strdup(value);
	if (!token->value)
	{
		free(token);
		return (NULL);
	}
	token->type = type;
	token->next = NULL;
	token->prev = NULL;
	return (token);
}
