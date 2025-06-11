/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbohme <pbohme@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 17:13:34 by pbohme            #+#    #+#             */
/*   Updated: 2025/01/20 15:47:44 by pbohme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

char	**get_paths_from_env(t_mini *mini, char *cmd)
{
	char	*env;
	char	**all_paths;

	env = ft_getenv("PATH", mini);
	if (!env)
	{
		ft_printf_stderr("minishell: ", cmd, ": No such file or directory");
		return (NULL);
	}
	all_paths = ft_split(env, ':');
	if (!all_paths)
	{
		perror("Error: Failed to split PATH");
		return (NULL);
	}
	return (all_paths);
}

char	*find_executable_in_paths(char **all_paths, char *cmd)
{
	char	*tmp_path;
	char	*path;
	int		i;

	i = 0;
	while (all_paths[i++])
	{
		tmp_path = ft_strjoin(all_paths[i], "/");
		if (!tmp_path)
		{
			perror("Error: Memory allocation failed for tmp_path");
			break ;
		}
		path = ft_strjoin(tmp_path, cmd);
		free(tmp_path);
		if (!path)
		{
			perror("Error: Memory allocation failed for path");
			break ;
		}
		if (access(path, F_OK | X_OK) == 0)
			return (path);
		free(path);
	}
	return (NULL);
}

int	is_path_specified(char *cmd)
{
	return (cmd[0] == '/' || (cmd[0] == '.' && (cmd[1] == '/' || \
		cmd[1] == '.')));
}

char	*ft_find_path(char *cmd, t_mini *mini)
{
	char	**all_paths;
	char	*path;

	if (is_path_specified(cmd))
	{
		if (access(cmd, F_OK | X_OK) == 0)
			return (ft_strdup(cmd));
		ft_printf_stderr("minishell: ", cmd, ": No such file or directory");
		return (NULL);
	}
	all_paths = get_paths_from_env(mini, cmd);
	if (!all_paths)
		return (NULL);
	path = find_executable_in_paths(all_paths, cmd);
	if (!path)
		ft_printf_stderr("minishell: ", cmd, ": command not found");
	free_split(all_paths);
	return (path);
}
