/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaned_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbohme <pbohme@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 15:00:36 by pbohme            #+#    #+#             */
/*   Updated: 2024/12/17 19:57:51 by pbohme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*fill_clean_quote(char *str, const char *new, char quote, int k)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (j < k)
	{
		if (new[j] == quote)
			j++;
		else
		{
			str[i] = new[j];
			i++;
			j++;
		}
	}
	str[i] = '\0';
	return (str);
}

char	*create_cleaned_quote(const char *new, char quote)
{
	int		k;
	int		count;
	char	*clean;

	k = 0;
	count = 0;
	while (new[k])
	{
		if (new[k] == ' ' && new[k - 1] == quote)
			break ;
		if (new[k] == quote)
			count++;
		k++;
	}
	while (new[k] != quote)
		k--;
	clean = (char *)malloc(k - count + 2);
	if (!clean)
		return (NULL);
	clean = fill_clean_quote(clean, new, quote, k);
	return (clean);
}

char	*clean_input(const char **input, char quote)
{
	const char	*new;
	char		*cleaned;
	int			i;

	new = *input;
	i = 0;
	while (**input)
	{
		if (**input == ' ' && *(*input - 1) == quote)
			break ;
		(*input)++;
		i++;
	}
	while (**input != quote)
	{
		(*input)--;
		i--;
	}
	(*input)++;
	while (is_whitespace(**input))
		(*input)++;
	cleaned = create_cleaned_quote(new, quote);
	return (cleaned);
}
