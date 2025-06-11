/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_snprintf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbohme <pbohme@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 17:22:32 by pbohme            #+#    #+#             */
/*   Updated: 2025/01/17 19:28:40 by pbohme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	ft_snprintf(char *full_path, char *dir, char *command)
{
	ft_strlcpy(full_path, dir, PATH_MAX);
	ft_strlcat(full_path, "/", PATH_MAX);
	ft_strlcat(full_path, command, PATH_MAX);
}
