/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbohme <pbohme@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 17:13:54 by pbohme            #+#    #+#             */
/*   Updated: 2024/11/26 17:55:06 by pbohme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	is_builtin(char *cmd)
{
	return (ft_strcmp(cmd, "echo") == 0 || ft_strcmp(cmd, "cd") == 0 
		|| ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "export") == 0 
		|| ft_strcmp(cmd, "unset") == 0 || ft_strcmp(cmd, "env") == 0 
		|| ft_strcmp(cmd, "exit") == 0);
}

void	execute_builtin(char *cmd, char **args, char ***envp, t_mini *mini)
{
	if (ft_strcmp(cmd, "echo") == 0)
		ft_echo(args, mini);
	else if (ft_strcmp(cmd, "cd") == 0)
		ft_cd(args, mini);
	else if (ft_strcmp(cmd, "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(cmd, "export") == 0)
		ft_export(args, envp, mini);
	else if (ft_strcmp(cmd, "unset") == 0)
		ft_unset(args, mini);
	else if (ft_strcmp(cmd, "env") == 0)
		ft_env(*envp);
	else if (ft_strcmp(cmd, "exit") == 0)
	{
		if (args && args[0])
			ft_exit(args, mini);
		else
			ft_exit(NULL, mini);
	}
}
