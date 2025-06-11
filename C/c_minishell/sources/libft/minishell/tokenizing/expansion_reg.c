/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_reg.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbohme <pbohme@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 11:43:09 by pbohme            #+#    #+#             */
/*   Updated: 2025/01/10 16:06:45 by pbohme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	rm_token(t_token **head, t_token *node_to_delete)
{
	if (!head || !*head || !node_to_delete)
		return ;
	if (*head == node_to_delete)
		*head = node_to_delete->next;
	if (node_to_delete->prev)
		node_to_delete->prev->next = node_to_delete->next;
	if (node_to_delete->next)
		node_to_delete->next->prev = node_to_delete->prev;
	free(node_to_delete->value);
	free(node_to_delete);
}

int	check_exit_code(t_token **tokens, t_mini **mini)
{
	char	*exit_code_str;
	t_token	*current;

	current = *tokens;
	if (current->value[2] != '\0')
		return (check_quote_expansion(current, current->value, (*mini)->our_env,
				(*mini)->exit_code), 0);
	else
	{
		exit_code_str = ft_itoa((*mini)->exit_code);
		if (!exit_code_str)
		{
			perror("Memory alloc failed for exit code");
			return (1);
		}
		free(current->value);
		current->value = exit_code_str;
		current = current->next;
		return (0);
	}
}

int	update_exp(t_token **tokens, t_token *current, t_mini **mini)
{
	char	*var_name;
	char	*expanded_value;

	var_name = current->value + 1;
	expanded_value = get_env_value(var_name, (*mini)->our_env);
	if (expanded_value)
		rewrite_tokens(tokens, current, expanded_value);
	else
	{
		rm_token(tokens, current);
		if (*tokens == NULL)
			return (1);
	}
	return (0);
}

int	check_reg_expansion(t_token **tokens, t_mini **mini)
{
	t_token	*cur;
	t_token	*next;

	cur = *tokens;
	while (cur != NULL)
	{
		next = cur->next;
		if (cur->value[0] == '$')
		{
			if (cur->value[1] == '?')
			{
				if (check_exit_code(&cur, mini) != 0)
					return (1);
			}
			else if (cur->value[1] == '\0' || !ft_isalnum(cur->value[1]))
				continue ;
			else
			{
				if (update_exp(tokens, cur, mini) == 1)
					return (2);
			}
		}
		cur = next;
	}
	return (0);
}
