/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbohme <pbohme@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 18:40:57 by pbohme            #+#    #+#             */
/*   Updated: 2025/01/20 13:23:09 by pbohme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*ft_read_cmd(void)
{
	char	*buf;

	buf = readline("minishell$ ");
	if (buf && *buf)
		add_history(buf);
	return (buf);
}

char	**create_env_copy(char **envp)
{
	int		count;
	int		i;
	char	**new_env;

	count = 0;
	while (envp[count] != NULL)
		count++;
	new_env = malloc((count + 1) * sizeof(char *));
	if (!new_env)
		return (NULL);
	i = 0;
	while (i < count)
	{
		new_env[i] = ft_strdup(envp[i]);
		if (!new_env[i])
		{
			while (--i >= 0)
				free (new_env[i]);
			free(new_env);
			return (NULL);
		}
		i++;
	}
	new_env[count] = NULL;
	return (new_env);
}

t_mini	*ft_init_mini(char **envp)
{
	t_mini	*mini;

	mini = malloc(sizeof(t_mini));
	if (!mini)
		return (NULL);
	mini->cmd_count = 0;
	mini->word_count = 0;
	mini->is_last_cmd = 0;
	mini->has_redirection = 0;
	mini->fork = -1;
	mini->org_stdin = dup(STDIN_FILENO);
	mini->org_stdout = dup(STDOUT_FILENO);
	mini->our_env = create_env_copy(envp);
	mini->is_terminal = -1;
	if (!mini->our_env)
	{
		free (mini);
		return (NULL);
	}
	mini->exit_code = 0;
	return (mini);
}

int	only_whitespace(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!is_whitespace(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	ft_free_all(t_AN **ast, t_mini **mini, char **input, \
			t_token **tokens)
{
	if (ast && *ast)
	{
		free_ast(*ast);
		*ast = NULL;
	}
	if (mini && *mini)
	{
		free_mini(*mini);
		*mini = NULL;
	}
	if (input && *input)
	{
		free(*input);
		*input = NULL;
	}
	if (tokens && *tokens)
	{
		free_tokens(*tokens);
		*tokens = NULL;
	}
}
