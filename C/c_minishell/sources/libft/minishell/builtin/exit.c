/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hreusing <hreusing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 16:12:45 by pbohme            #+#    #+#             */
/*   Updated: 2025/01/06 13:54:14 by hreusing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	parse_exit_code(const char *value)
{
	long	result;
	char	*endptr;

	if (!value)
		return (0);
	result = ft_stol(value, &endptr, 10);
	if (endptr == value || *endptr != '\0')
	{
		fprintf(stderr, "exit: %s: numeric argument required\n", value);
		return (2);
	}
	if (result > 255 || result < 0)
		return (result % 256);
	return ((int)result);
}

bool	ft_exit(char **args, t_mini *mini)
{
	int	exit_code;

	exit_code = mini->exit_code;
	printf("exit\n");
	if (args && args[0] && args[1])
	{
		fprintf(stderr, "minishell: exit: too many arguments\n");
		mini->exit_code = 1;
		return (false);
	}
	if (args && args[0])
	{
		exit_code = parse_exit_code(args[0]);
		mini->exit_code = exit_code;
	}
	else 
		exit_code = 0;
	exit(exit_code);
	return (true);
}
