/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbohme <pbohme@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 13:46:07 by pbohme            #+#    #+#             */
/*   Updated: 2025/01/20 15:41:01 by pbohme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	ft_perror_cd(t_mini **mini, char *old_pwd)
{
	perror("cd");
	if (old_pwd)
		free(old_pwd);
	(*mini)->exit_code = 1;
}

char	*ft_no_args(t_mini *mini, char **args)
{
	char	*path;

	if (!args || !args[0])
		path = ft_getenv("HOME", mini);
	else
		path = getenv("HOME");
	if (!path)
	{
		{
			ft_putendl_fd("minishell: cd: HOME not set", 2);
			mini->exit_code = 1;
			return (NULL);
		}
	}
	return (path);
}

void	ft_set_all_env(char *old_pwd, char *cwd, t_mini *mini)
{
	ft_setenv("OLDPWD", ft_strlen("OLDPWD"), old_pwd, mini);
	ft_setenv("PWD", ft_strlen("PWD"), cwd, mini);
}

void	too_many_args(t_mini **mini)
{
	ft_putendl_fd("minishell: cd: too many arguments", 2);
	(*mini)->exit_code = 1;
}

void	ft_cd(char **args, t_mini *mini)
{
	char	*path;
	char	*old_pwd;
	char	cwd[PATH_MAX];

	if (!args || !args[0] || args[0][0] == '~')
	{
		path = ft_no_args(mini, args);
		if (!path)
			return ;
	}
	else if (args[1])
		return (too_many_args(&mini));
	else if (args[0] != NULL)
		path = args[0];
	old_pwd = getcwd(NULL, 0);
	if (!old_pwd)
		return (ft_perror_cd(&mini, NULL));
	if (chdir(path) != 0)
		return (ft_perror_cd(&mini, old_pwd));
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		ft_set_all_env(old_pwd, cwd, mini);
	else
		ft_perror_cd(&mini, old_pwd);
	free(old_pwd);
	mini->exit_code = 0;
}
