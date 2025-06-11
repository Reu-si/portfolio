/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbohme <pbohme@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 15:05:36 by pbohme            #+#    #+#             */
/*   Updated: 2025/01/10 19:27:02 by pbohme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	check_double_quotes(char *input, int double_quote, int single_quote)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (double_quote == 0 && single_quote > 0)
			return (0);
		if (input[i] == '\'')
			single_quote--;
		if (input[i] == '\"')
			double_quote--;
		i++;
	}
	return (1);
}

int	check_single_quotes(char *input, int double_quote, int single_quote)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (single_quote == 0 && double_quote > 0)
			return (0);
		if (input[i] == '\"')
			double_quote--;
		if (input[i] == '\'')
			single_quote--;
		i++;
	}
	return (1);
}

int	check_quote_position(char *input, int double_quote, int single_quote)
{
	if (double_quote % 2 == 1)
	{
		if (check_double_quotes(input, double_quote, single_quote) == 0)
			return (0);
	}
	else if (single_quote % 2 == 1)
	{
		if (check_single_quotes(input, double_quote, single_quote) == 0)
			return (0);
	}
	return (1);
}

int	check_quote_count(char *input)
{
	int	double_quote;
	int	single_quote;
	int	i;

	double_quote = 0;
	single_quote = 0;
	i = 0;
	while (input[i])
	{
		if (input[i] == '\'')
			single_quote++;
		if (input[i] == '\"')
			double_quote++;
		i++;
	}
	if ((double_quote % 2 == 1 && (single_quote == 0 || single_quote % 2 != 0))
		|| (single_quote % 2 == 1 && (double_quote == 0 || double_quote
				% 2 != 0)))
		return (printf("Open qoutes are not handled.\n"), 1);
	else if (((double_quote % 2 == 1 && single_quote != 0 && single_quote
				% 2 == 0) || (single_quote % 2 == 1 && double_quote != 0
				&& double_quote % 2 == 0)) && check_quote_position(input,
			double_quote, single_quote) == 1)
		return (printf("Open qoutes are not handled.\n"), 1);
	return (0);
}

int	ft_tokenize_quotes(t_token **head, t_token **tail, const char **input)
{
	char		quote;
	t_token		*quoted_token;
	char		*quoted_char;

	quote = **input;
	(*input)++;
	if (**input == quote && (*input)[1] == '\0')
		return ((*input)++, 1);
	quoted_char = clean_input(input, quote);
	if (quote == '\'')
		quoted_token = create_token(quoted_char, T_SINGLE_QUOTE);
	else
		quoted_token = create_token(quoted_char, T_DOUBLE_QUOTE);
	free(quoted_char);
	if (!quoted_token)
		return (0);
	append_to_list(head, tail, quoted_token);
	return (1);
}
