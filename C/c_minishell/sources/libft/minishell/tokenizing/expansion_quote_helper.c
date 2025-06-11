/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_quote_helper.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbohme <pbohme@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 19:40:51 by pbohme            #+#    #+#             */
/*   Updated: 2025/01/15 13:33:07 by pbohme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	calculate_new_value(t_exp_quote **new, char *str, int *i, char **envp)
{
	(*new)->var_len = 0;
	while (str[*i + 1 + (*new)->var_len] && (ft_isalnum(str[*i + 1 + \
			(*new)->var_len]) || str[*i + 1 + (*new)->var_len] == '_'))
		(*new)->var_len++;
	(*new)->var_name = ft_strndup(&str[*i + 1], (*new)->var_len);
	(*new)->expanded_value = get_env_value((*new)->var_name, envp);
	if ((*new)->expanded_value)
		(*new)->new_len += strlen((*new)->expanded_value) - \
		((*new)->var_len + 1);
	free((*new)->var_name);
	free((*new)->expanded_value);
	*i += (*new)->var_len + 1;
}

void	calculate_new_str(char *str, t_exp_quote **new, char **envp)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			if (str[i + 1] == '?')
			{
				(*new)->new_len += ft_strlen((*new)->exit_code_str) - 2;
				i += 2;
			}
			else if (str[i + 1] == '\0' || !ft_isalnum(str[i + 1]))
				i++;
			else
				calculate_new_value(new, str, &i, envp);
		}
		else
			i++;
	}
}

int	count_var_len(t_exp_quote **new, int *i)
{
	while ((*new)->str[(*i) + 1 + (*new)->var_len] 
		&& (isalnum((*new)->str[(*i) + 1 + (*new)->var_len]) 
			|| (*new)->str[(*i) + 1 + (*new)->var_len] == '_'))
		return (1);
	return (0);
}

void	fill_expanded_value(t_exp_quote **new, int *i, int *j, char **envp)
{
	if ((*new)->str[(*i) + 1] == '?')
	{
		ft_strcpy(&((*new)->expanded_str[*j]), (*new)->exit_code_str);
		*j += ft_strlen((*new)->exit_code_str);
		*i += 2;
	}
	else if ((*new)->str[(*i) + 1] == '\0' || !ft_isalnum((*new)->str[*i + 1]))
		(*new)->expanded_str[(*j)++] = (*new)->str[(*i)++];
	else
	{
		(*new)->var_len = 0;
		while (count_var_len(new, i))
			(*new)->var_len++;
		(*new)->var_name = ft_strndup(&(*new)->str[(*i) + 1], (*new)->var_len);
		(*new)->expanded_value = get_env_value((*new)->var_name, envp);
		if ((*new)->expanded_value)
		{
			ft_strcpy(&((*new)->expanded_str[*j]), (*new)->expanded_value);
			*j += ft_strlen((*new)->expanded_value);
			free((*new)->expanded_value);
		}
		free((*new)->var_name);
		*i += (*new)->var_len + 1;
	}
}

void	fill_expanded_str(t_exp_quote **new, char **envp)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while ((*new)->str[i])
	{
		if ((*new)->str[i] == '$')
			fill_expanded_value(new, &i, &j, envp);
		else
			(*new)->expanded_str[j++] = (*new)->str[i++];
	}
	(*new)->expanded_str[j] = '\0';
}
