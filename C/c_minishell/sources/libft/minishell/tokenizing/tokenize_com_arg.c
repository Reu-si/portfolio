/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_com_arg.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbohme <pbohme@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 17:19:09 by pbohme            #+#    #+#             */
/*   Updated: 2025/01/17 14:21:22 by pbohme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*found_quotes_in_input(const char **input, const char *start, \
	char *newvalue)
{
	char	quote;
	char	*temp_value;
	char	*joined_value;

	quote = **input;
	(*input)++;
	start = *input;
	while (**input && **input != quote)
		(*input)++;
	if (**input != quote)
		return (NULL);
	temp_value = ft_strndup(start, *input - start);
	if (!temp_value)
		return (NULL);
	if (newvalue)
	{
		joined_value = ft_strjoin(newvalue, temp_value);
		free(newvalue);
		newvalue = joined_value;
	}
	else
		newvalue = strdup(temp_value);
	(*input)++;
	return (free(temp_value), newvalue);
}

char	*no_quotes_in_input(const char **input, const char *start, \
			char *newvalue)
{
	char	*temp_value;
	char	*joined_value;

	start = *input;
	while (**input && !is_whitespace(**input) && **input != '|'
		&& **input != '<' && **input != '>' && **input != '\''
		&& **input != '\"')
		(*input)++;
	temp_value = ft_strndup(start, *input - start);
	if (!temp_value)
		return (NULL);
	if (newvalue)
	{
		joined_value = ft_strjoin(newvalue, temp_value);
		free(newvalue);
		newvalue = joined_value;
	}
	else
		newvalue = strdup(temp_value);
	free(temp_value);
	if (!newvalue)
		return (NULL);
	return (newvalue);
}

int	check_type(t_token **word_token)
{
	if (!(*word_token)->prev || (*word_token)->prev->type == T_PIPE
		|| (*word_token)->prev->type == T_REDIRECT_IN
		|| (*word_token)->prev->type == T_REDIRECT_OUT
		|| (*word_token)->prev->type == T_APPEND
		|| (*word_token)->prev->type == T_HEREDOC)
		return (1);
	else
		return (0);
}

int	check_word_token(char *newvalue, t_token **head, t_token **tail)
{
	t_token	*word_token;

	word_token = create_token(newvalue, T_ARGUMENT);
	free(newvalue);
	if (!word_token)
		return (1);
	append_to_list(head, tail, word_token);
	if (check_type(&word_token) == 1)
		word_token->type = T_COMMAND;
	return (0);
}

int	ft_tokenize_com_arg(t_token **head, t_token **tail, const char **input)
{
	const char	*start;
	char		*newvalue;

	newvalue = NULL;
	start = *input;
	while (**input && !is_whitespace(**input) && **input != '|'
		&& **input != '<' && **input != '>')
	{
		if (**input == '\'' || **input == '\"')
		{
			newvalue = found_quotes_in_input(input, start, newvalue);
			if (!newvalue)
				return (0);
		}
		else
		{
			newvalue = no_quotes_in_input(input, start, newvalue);
			if (!newvalue)
				return (0);
		}
	}
	if (check_word_token(newvalue, head, tail) == 1)
		return (0);
	return (1);
}

// int	ft_tokenize_com_arg(t_token **head, t_token **tail, const char **input)
// {
// 	const char	*start;
// 	char		*newvalue;
// 	t_token		*word_token;
// 	// char		*temp_value;
// 	// char		quote;
// 	// char		*joined_value;
// 	newvalue = NULL;
// 	start = *input;
// 	while (**input && !is_whitespace(**input) && **input != '|'
// 		&& **input != '<' && **input != '>')
// 	{
// 		if (**input == '\'' || **input == '\"')
// 		{
// 			newvalue = found_quotes_in_input(input, start, newvalue);
// 			if (!newvalue)
// 				return (0);
// 			// quote = **input;
// 			// (*input)++;
// 			// start = *input;
// 			// while (**input && **input != quote)
// 			// 	(*input)++;
// 			// if (**input != quote)
// 			// 	return (0);
// 			// temp_value = ft_strndup(start, *input - start);
// 			// if (!temp_value)
// 			// 	return (0);
// 			// if (newvalue)
// 			// {
// 			// 	joined_value = ft_strjoin(newvalue, temp_value);
// 			// 	free (newvalue);
// 			// 	newvalue = joined_value;
// 			// }
// 			// else
// 			// 	newvalue = strdup(temp_value);
// 			// free(temp_value);
// 			// (*input)++;
// 		}
// 		else
// 		{
// 			newvalue = no_quotes_in_input(input, start, newvalue);
// 			if (!newvalue)
// 				return (0);
// 			// start = *input;
// 			// while (**input && !is_whitespace(**input) && **input != '|'
// 			// 	&& **input != '<' && **input != '>' && **input != '\''
// 			// 	&& **input != '\"')
// 			// 	(*input)++;
// 			// temp_value = ft_strndup(start, *input - start);
// 			// if (!temp_value)
// 			// 	return (0);
// 			// if (newvalue)
// 			// {
// 			// 	joined_value = ft_strjoin(newvalue, temp_value);
// 			// 	free(newvalue);
// 			// 	newvalue = joined_value;
// 			// }
// 			// else
// 			// 	newvalue = strdup(temp_value);
// 			// free(temp_value);
// 			// if (!newvalue)
// 			// 	return (0);
// 		}
// 	}
// 	word_token = create_token(newvalue, T_ARGUMENT);
// 	free(newvalue);
// 	if (!word_token)
// 		return (0);
// 	append_to_list(head, tail, word_token);
// 	if (!word_token->prev || word_token->prev->type == T_PIPE
// 		|| word_token->prev->type == T_REDIRECT_IN
// 		|| word_token->prev->type == T_REDIRECT_OUT
// 		|| word_token->prev->type == T_APPEND
// 		|| word_token->prev->type == T_HEREDOC)
// 		word_token->type = T_COMMAND;
// 	return (1);
// }