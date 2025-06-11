/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbohme <pbohme@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 14:19:59 by pbohme            #+#    #+#             */
/*   Updated: 2025/01/17 13:38:22 by pbohme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	update_existing_env(const char *key, size_t key_len, \
const char *value, t_mini *mini)
{
	int		i;
	char	**env;
	char	*new_entry;

	env = mini->our_env;
	i = 0;
	while (env[i] != NULL)
	{
		if (strncmp(env[i], key, key_len) == 0 && env[i][key_len] == '=') 
		{
			free(env[i]);
			new_entry = ft_sprintf_simple(key, value);
			env[i] = new_entry;
			return (1);
		}
		i++;
	}
	return (0);
}

int	count_env(char **env)
{
	int	count;

	count = 0;
	while (env[count] != NULL)
		count++;
	return (count);
}

int	ft_setenv(const char *key, size_t key_len, const char *value, t_mini *mini)
{
	char	**env;
	char	*new_entry;
	char	**new_env;
	int		i;
	int		env_count;

	env = mini->our_env;
	if (update_existing_env(key, key_len, value, mini) == 1)
		return (0);
	new_entry = ft_sprintf_simple(key, value);
	env_count = count_env(env);
	new_env = malloc((env_count + 2) * sizeof(char *));
	if (!new_env)
		return (free(new_entry), -1);
	i = 0;
	while (i < env_count)
	{
		new_env[i] = env[i];
		i++;
	}
	new_env[env_count] = new_entry;
	new_env[env_count + 1] = NULL;
	free(mini->our_env);
	mini->our_env = new_env;
	return (0);
}

void	check_for_eq_sign(char *args, char **key, char **value)
{
	char	*equal_sign;

	equal_sign = ft_strchr(args, '=');
	if (equal_sign)
	{
		*key = ft_strndup(args, equal_sign - args);
		*value = ft_strdup(equal_sign + 1);
	}
	else
	{
		*key = ft_strdup(args);
		*value = NULL;
	}
}
