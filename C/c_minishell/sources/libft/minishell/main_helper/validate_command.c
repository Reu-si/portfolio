/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbohme <pbohme@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 17:13:40 by pbohme            #+#    #+#             */
/*   Updated: 2025/01/20 13:23:00 by pbohme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*find_command_path(const char *command, char **env)
{
	char		*path;
	char		*path_copy;
	char		*dir;
	struct stat	st;
	char		full_path[PATH_MAX];

	path = get_env_value("PATH", env);
	if (!path)
		return (NULL);
	path_copy = ft_strdup(path);
	free(path);
	if (!path_copy)
		return (NULL);
	dir = ft_strtok(path_copy, ":");
	while (dir)
	{
		ft_snprintf(full_path, dir, (char *)command);
		if (stat(full_path, &st) == 0)
		{
			free(path_copy);
			return (ft_strdup(full_path));
		}
		dir = ft_strtok(NULL, ":");
	}
	return (free(path_copy), NULL);
}

int	check_t_value(t_token **tokens)
{
	if ((*tokens)->type == T_COMMAND && ((*tokens)->value[0] == '.'
			|| (*tokens)->value[0] == '/'))
		return (1);
	return (0);
}

int	valid_cmd(t_token *tokens, t_mini *mini)
{
	struct stat	st;
	char		*cmd_path;

	if (check_t_value(&tokens) == 1)
	{
		cmd_path = find_command_path(tokens->value, mini->our_env);
		if (cmd_path)
			return (free(cmd_path), 0);
		if (stat(tokens->value, &st) == 0)
		{
			if (S_ISDIR(st.st_mode))
			{
				ft_putendl_fd(" Is a directory", 2);
				mini->exit_code = 126;
				return (1);
			}
			else if (!(st.st_mode & S_IXUSR))
			{
				fprintf(stderr, " Permission denied\n");
				mini->exit_code = 126;
				return (1);
			}
		}
	}
	return (0);
}
