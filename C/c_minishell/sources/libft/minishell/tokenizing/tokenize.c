/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbohme <pbohme@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:28:30 by pbohme            #+#    #+#             */
/*   Updated: 2025/01/20 16:52:00 by pbohme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	check_tokenizing(const char **input, t_token **head, t_token **tail)
{
	if (**input == '|')
	{
		if (ft_tokenize_pipe(head, tail) == 0)
			return (1);
		(*input)++;
	}
	else if (**input == '\'' || **input == '\"')
	{
		if (ft_tokenize_quotes(head, tail, input) == 0)
			return (1);
	}
	else if (**input == '<' || **input == '>')
	{
		if (ft_tokenize_red_app_her(head, tail, input) == 0)
			return (1);
	}
	else if (**input && !is_whitespace(**input) && **input != '|'
		&& **input != '\'' && **input != '\"' && **input != '<'
		&& **input != '>')
	{
		if (ft_tokenize_com_arg(head, tail, input) == 0)
			return (1);
	}
	return (0);
}

int	check_empty_pipes(const char *input)
{
	int	i;
	int	j;

	i = 0;
	while (input[i])
	{
		if (input[i] == '|')
		{
			j = i + 1;
			while (input[j] && is_whitespace(input[j]))
				j++;
			if (input[j] == '|' || input[j] == '<' || input[j] == '>'
				|| input[j] == '\0')
			{
				ft_putendl_fd("minishell: syntax error near unexpected" 
					"token '|'", 2);
				return (0);
			}
		}
		i++;
	}
	return (1);
}

t_token	*tokenize_input(const char *input)
{
	t_token	*head;
	t_token	*tail;

	head = NULL;
	tail = NULL;
	if (check_quote_count((char *)input) == 1)
		return (NULL);
	if (*input == '|')
		return (ft_putendl_fd("minishell: syntax error near unexpected"
				"token '|'", 2), NULL);
	if (!check_empty_pipes(input))
		return (NULL);
	while (*input)
	{
		skip_whitespace(&input);
		if (*input == '\0')
			break ;
		else if (check_tokenizing(&input, &head, &tail) == 1)
		{
			free_tokens(head);
			return (NULL);
		}
	}
	return (head);
}
