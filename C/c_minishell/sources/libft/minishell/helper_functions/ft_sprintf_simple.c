/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprintf_simple.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbohme <pbohme@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:18:48 by pbohme            #+#    #+#             */
/*   Updated: 2024/12/05 15:01:46 by pbohme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*ft_strcpy(char *dst, const char *src)
{
	char	*orig;

	orig = dst;
	while (*src != '\0')
	{
		*dst = *src;
		dst++;
		src++;
	}
	*dst = '\0';
	return (orig);
}

char	*ft_strcat(char *dst, const char *src)
{
	char	*ptr;

	ptr = dst;
	while (*ptr != '\0')
		ptr++;
	while (*src != '\0')
	{
		*ptr = *src;
		ptr++;
		src++;
	}
	*ptr = '\0';
	return (dst);
}

char	*ft_sprintf_simple(const char *key, const char *value)
{
	char	*new_entry;

	new_entry = malloc(strlen(key) + strlen(value) + 2);
	if (!new_entry)
		return (NULL);
	ft_strcpy(new_entry, key);
	ft_strcat(new_entry, "=");
	ft_strcat(new_entry, value);
	return (new_entry);
}
