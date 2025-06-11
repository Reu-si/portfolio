/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hreusing <hreusing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 17:21:48 by pbohme            #+#    #+#             */
/*   Updated: 2025/01/20 18:22:30 by hreusing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*get_env_value(const char *var_name, char **envp)
{
	size_t	len;
	int		i;
	char	*value;

	len = ft_strlen(var_name);
	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], var_name, len) == 0 && envp[i][len] == '=')
		{
			value = ft_strdup(envp[i] + len + 1);
			if (value == NULL)
			{
				ft_putendl_fd("Error: Mem alloc failed.", 2);
				return (NULL);
			}
			return (value);
		}
		i++;
	}
	return (NULL);
}

int	check_expansion(t_token **tokens, char **envp, t_mini *mini)
{
	t_token	*current;
	t_token	*next;

	current = *tokens;
	while (current != NULL)
	{
		next = current->next;
		if ((current->value[0] == '$' && current->value[1] == '\0')
			|| (current->type == T_DOUBLE_QUOTE
				&& current->prev->type == T_HEREDOC))
			break ;
		if ((current->type == T_ARGUMENT && current->value[0] == '$')
			|| (current->type == T_COMMAND && current->value[0] == '$')
			|| current->type == T_DOUBLE_QUOTE)
		{
			if (current->type == T_DOUBLE_QUOTE)
				check_quote_expansion(current, current->value, envp,
					mini->exit_code);
			else if (check_reg_expansion(tokens, &mini) != 0)
				return (1);
		}
		current = next;
	}
	return (0);
}
