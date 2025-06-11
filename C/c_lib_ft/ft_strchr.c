/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hreusing <hreusing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 14:33:12 by hreusing          #+#    #+#             */
/*   Updated: 2024/05/11 13:51:35 by hreusing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(char const *str, int c)
{
	while (*str)
	{
		if (*str == (char)c)
			return ((char *)str);
		str++;
	}
	if (*str == (char)c)
		return ((char *)str);
	else
		return (NULL);
}

// char	*ft_strchr(char *str, int chr)
// {
// 	int		i;

// 	i = 0;
// 	if (chr > 255)
// 		chr = chr % 256;
// 	if (chr < 0)
// 		chr = 265 + (chr % 256);
// 	if (!str)
// 		return (NULL);
// 	while (str[i])
// 	{
// 		if (str[i] == chr)
// 			return (&str[i]);
// 		i++;
// 	}
// 	if (str[i] == chr)
// 		return (&str[i]);
// 	return (0);
// }
//
// int	main(void)
// {
// 	printf("%s", ft_strchr(((void*)0), '\0'));
// }
