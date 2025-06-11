/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_attributes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hreusing <hreusing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 14:17:44 by hreusing          #+#    #+#             */
/*   Updated: 2025/01/20 17:28:22 by hreusing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	ft_save_term_attr(t_mini *mini)
{
	if (isatty(STDIN_FILENO))
	{
		if (tcgetattr(STDIN_FILENO, &mini->old_term) == -1)
		{
			perror("tcgetattr");
			exit(EXIT_FAILURE);
		}
		mini->is_terminal = 1;
	}
	else
	{
		mini->is_terminal = 0;
	}
}

void	ft_reset_term_attr(t_mini *mini)
{
	if (mini->is_terminal)
	{
		if (isatty(STDIN_FILENO))
		{
			if (tcsetattr(STDIN_FILENO, TCSANOW, &mini->old_term) == -1)
			{
				perror("tcsetattr");
				exit(EXIT_FAILURE);
			}
		}
	}
}
