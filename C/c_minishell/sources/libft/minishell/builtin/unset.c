/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbohme <pbohme@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 17:35:58 by pbohme            #+#    #+#             */
/*   Updated: 2025/01/17 13:53:54 by pbohme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	create_new_env(int count, int i, t_mini *mini)
{
	char	**env;
	char	**new_env;
	int		j;

	env = mini->our_env;
	j = 0;
	new_env = malloc(count * sizeof(char *));
	if (!new_env)
		return (1);
	while (j < i)
	{
		new_env[j] = env[j];
		j++;
	}
	j = i;
	while (j < count - 1)
	{
		new_env[j] = env[j + 1];
		j++;
	}
	new_env[count - 1] = NULL;
	free(mini->our_env);
	mini->our_env = new_env;
	return (0);
}

int	ft_unsetenv(char *key, size_t key_len, t_mini *mini)
{
	char	**env;
	int		i;
	int		env_count;

	if (!key || !mini->our_env)
		return (-1);
	env = mini->our_env;
	i = 0;
	env_count = 0;
	while (env[env_count] != NULL)
		env_count++;
	while (env[i] != NULL)
	{
		if (strncmp(env[i], key, key_len) == 0
			&& env[i][key_len] == '=')
		{
			free(env[i]);
			if (create_new_env(env_count, i, mini) == 1)
				return (-1);
			return (0);
		}
		i++;
	}
	return (-1);
}

void	ft_unset(char **args, t_mini *mini)
{
	int	i;

	if (!args)
		return ;
	i = 0;
	while (args[i] != NULL)
	{
		ft_unsetenv(args[i], ft_strlen(args[i]), mini);
		i++;
	}
}
