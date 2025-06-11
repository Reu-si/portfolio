/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_quote.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbohme <pbohme@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 19:04:18 by pbohme            #+#    #+#             */
/*   Updated: 2025/01/15 13:33:06 by pbohme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

t_exp_quote	*init_ex_quote(char *string, int exit_code)
{
	t_exp_quote	*new;

	new = malloc(sizeof(t_exp_quote));
	if (!new)
		return (NULL);
	new->new_len = ft_strlen(string);
	new->exit_code_str = ft_itoa(exit_code);
	new->str = string;
	return (new);
}

int	create_expanded_str(t_exp_quote **new)
{
	(*new)->expanded_str = (char *)ft_calloc(((*new)->new_len + 1), \
		sizeof(char));
	if (!(*new)->expanded_str)
	{
		perror("memory allocation failed");
		free((*new)->exit_code_str);
		return (1);
	}
	return (0);
}

void	check_quote_expansion(t_token *token, char *str, char **envp,
		int exit_code)
{
	t_exp_quote	*new;

	new = init_ex_quote(str, exit_code);
	calculate_new_str(str, &new, envp);
	if (create_expanded_str(&new) == 1)
		return ;
	ft_memset(new->expanded_str, 0, new->new_len + 1);
	fill_expanded_str(&new, envp);
	free(token->value);
	token->value = new->expanded_str;
	free(new->exit_code_str);
	free(new);
}

// void	check_quote_expansion(t_token *token, char *str, char **envp,
// 		int exit_code)
// {
// 	int			i;
// 	int			j;
// 	t_exp_quote	*new;
// 	int		var_len;
// 	char	*expanded_str;
// 	char	*exit_code_str;
// 	char	*var_name;
// 	char	*expanded_value;
// 	size_t	new_len;

// 	i = 0;
// 	new_len = ft_strlen(str);
// 	exit_code_str = ft_itoa(exit_code);
// 	while (str[i])
// 	{
// 		if (str[i] == '$')
// 		{
// 			if (str[i + 1] == '?')
// 			{
// 				new_len += ft_strlen(exit_code_str) - 2;
// 				i += 2;
// 			}
// 			else if (str[i + 1] == '\0' || !ft_isalnum(str[i + 1]))
// 				i++;
// 			else
// 			{
// 				var_len = 0;
// 				while (str[i + 1 + var_len] && (ft_isalnum(str[i + 1 + var_len])
// 						|| str[i + 1 + var_len] == '_'))
// 					var_len++;
// 				var_name = ft_strndup(&str[i + 1], var_len);
// 				expanded_value = get_env_value(var_name, envp);
// 				if (expanded_value)
// 					new_len += strlen(expanded_value) - (var_len + 1);
// 				free(var_name);
// 				free(expanded_value);
// 				i += var_len + 1;
// 			}
// 		}
// 		else
// 			i++;
// 	}
// 	expanded_str = (char *)ft_calloc((new_len + 1), sizeof(char));
// 	if (!expanded_str)
// 	{
// 		perror("memory allocation failed");
// 		free(exit_code_str);
// 		return ;
// 	}
// 	ft_memset(expanded_str, 0, new_len + 1);
// 	i = 0;
// 	j = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == '$')
// 		{
// 			if (str[i + 1] == '?')
// 			{
// 				strcpy(&expanded_str[j], exit_code_str);
// 				j += ft_strlen(exit_code_str);
// 				i += 2;
// 			}
// 			else if (str[i + 1] == '\0' || !ft_isalnum(str[i + 1]))
// 				expanded_str[j++] = str[i++];
// 			else
// 			{
// 				var_len = 0;
// 				while (str[i + 1 + var_len] && (isalnum(str[i + 1 + var_len])
// 						|| str[i + 1 + var_len] == '_'))
// 					var_len++;
// 				var_name = ft_strndup(&str[i + 1], var_len);
// 				expanded_value = get_env_value(var_name, envp);
// 				if (expanded_value)
// 				{
// 					strcpy(&expanded_str[j], expanded_value);
// 					j += ft_strlen(expanded_value);
// 					free(expanded_value);
// 				}
// 				free(var_name);
// 				i += var_len + 1;
// 			}
// 		}
// 		else
// 			expanded_str[j++] = str[i++];
// 	}
// 	expanded_str[j] = '\0';
// 	free(token->value);
// 	token->value = expanded_str;
// 	free(exit_code_str);
// }
