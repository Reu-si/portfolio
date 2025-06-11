/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbohme <pbohme@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 16:09:40 by pbohme            #+#    #+#             */
/*   Updated: 2025/01/20 15:52:03 by pbohme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	is_valid_identifier(const char *key)
{
	size_t	i;

	if (!key || !*key)
		return (0);
	if (!ft_isalpha(key[0]) && key[0] != '_')
		return (0);
	i = 1;
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	export_no_args(char ***envp, t_mini *mini)
{
	char	**env;

	env = *envp;
	while (*env != NULL)
	{
		printf("declare -x %s\n", *env);
		env++;
	}
	mini->exit_code = 0;
}

void	check_valid_id(char *key, char *value, char *args, t_mini *mini)
{
	int	result;

	if (!is_valid_identifier(key))
	{
		ft_printf_stderr("minishell: export: `", args, \
		"': not a valid identifier");
		mini->exit_code = 1;
	}
	else if (value && is_valid_identifier(key))
	{
		result = ft_setenv(key, ft_strlen(key), value, mini);
		if (result != 0)
		{
			ft_putendl_fd("Failed to set environment variable", 2);
			mini->exit_code = 1;
		}
		mini->exit_code = 0;
	}
	else
		mini->exit_code = 0;
}

void	ft_export(char **args, char ***envp, t_mini *mini)
{
	char	*value;
	char	*key;
	int		i;

	if (!args || !args[0])
		return (export_no_args(envp, mini));
	i = 0;
	while (args[i] != NULL)
	{
		key = NULL;
		value = NULL;
		check_for_eq_sign(args[i], &key, &value);
		check_valid_id(key, value, args[i], mini);
		free(key);
		if (value)
			free(value);
		i++;
	}
}
