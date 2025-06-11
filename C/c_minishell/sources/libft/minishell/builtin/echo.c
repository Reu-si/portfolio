/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbohme <pbohme@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 14:56:38 by pbohme            #+#    #+#             */
/*   Updated: 2025/01/15 14:21:51 by pbohme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	ft_echo(char **args, t_mini *mini)
{
	int	newline;
	int	i;

	newline = 1;
	i = 0;
	if (!args || !args[0])
	{
		printf("\n");
		return ;
	}
	if (args[0] && ft_strcmp(args[0], "-n") == 0)
	{
		newline = 0;
		i++;
	}
	while (args[i] != NULL)
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
	mini->exit_code = 0;
}
