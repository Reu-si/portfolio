/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rewrite_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbohme <pbohme@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 13:50:27 by pbohme            #+#    #+#             */
/*   Updated: 2025/01/10 19:27:18 by pbohme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	check_no_space( char *expanded_value, t_token **current)
{
	if (ft_strchr(expanded_value, ' ') == NULL)
	{
		free((*current)->value);
		(*current)->value = expanded_value;
		return (1);
	}
	return (0);
}

void	create_expanded_tokens(char *expanded_value, \
t_token **first_n_token, t_token **last_n_token)
{
	char	**tokens;
	t_token	*new_t;
	int		i;

	i = 0;
	tokens = ft_split(expanded_value, ' ');
	if (!tokens)
		return (free(expanded_value));
	while (tokens[i] != NULL)
	{
		if (i == 0)
			new_t = create_token(tokens[i], T_COMMAND);
		else
			new_t = create_token(tokens[i], T_ARGUMENT);
		append_to_list(first_n_token, last_n_token, new_t);
		free(tokens[i]);
		i++;
	}
	free(tokens);
	free(expanded_value);
}

void	rewrite_tokens(t_token **head, t_token *current, \
char *expanded_value)
{
	t_token	*temp_next;
	t_token	*first_n_token;
	t_token	*last_n_token;

	temp_next = current->next;
	first_n_token = NULL;
	last_n_token = NULL;
	if (check_no_space(expanded_value, &current) == 1)
		return ;
	create_expanded_tokens(expanded_value, &first_n_token, &last_n_token);
	if (current->prev)
		current->prev->next = first_n_token;
	else
		*head = first_n_token;
	if (first_n_token)
		first_n_token->prev = current->prev;
	if (temp_next)
	{
		last_n_token->next = temp_next;
		temp_next->prev = last_n_token;
	}
	free(current->value);
	free(current);
}
