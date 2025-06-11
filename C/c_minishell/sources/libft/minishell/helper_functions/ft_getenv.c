/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbohme <pbohme@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 15:29:31 by pbohme            #+#    #+#             */
/*   Updated: 2025/01/20 15:41:43 by pbohme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*ft_getenv(const char *name, t_mini *mini)
{
	int		i;
	size_t	len;

	if (!name || !mini || !mini->our_env)
		return (NULL);
	len = ft_strlen(name);
	i = 0;
	while (mini->our_env[i])
	{
		if (ft_strncmp(mini->our_env[i], name, len) == 0
			&& mini->our_env[i][len] == '=')
			return (&mini->our_env[i][len + 1]);
		i++;
	}
	return (NULL);
}
