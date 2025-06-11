/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hreusing <hreusing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 14:50:40 by hreusing          #+#    #+#             */
/*   Updated: 2024/05/11 13:52:44 by hreusing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(char const *str, int c)
{
	char const	*aux;

	aux = NULL;
	while (*str)
	{
		if (*str == (char)c)
			aux = str;
		str++;
	}
	if (*str == (char)c)
		return ((char *)str);
	else
		return ((char *)aux);
}

// char	*ft_strrchr(char *str, int chr)
// {
// 	char	*ptr;
// 	int		i;

// 	i = 0;
// 	ptr = 0;
// 	if (!str)
// 		return (NULL);
// 	while (str[i])
// 	{
// 		if (str[i] == (char)chr)
// 			ptr = &str[i];
// 		i++;
// 	}
// 	if (str[i] == (char)chr)
// 		return (&str[i]);
// 	return (ptr);
// }

// int	main(void)
// {
// 	printf("%s", ft_strrchr(((void*)0), '\0'));
// }
