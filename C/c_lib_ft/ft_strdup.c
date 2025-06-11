/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hreusing <hreusing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 11:54:25 by hreusing          #+#    #+#             */
/*   Updated: 2024/05/11 13:51:45 by hreusing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*str_new(size_t n)
{
	char	*str;

	str = (char *)malloc(sizeof(char) * (n + 1));
	if (!str)
		return (NULL);
	return (str);
}

char	*ft_strdup(char const *src)
{
	char	*dest;
	char	*start;

	dest = str_new(ft_strlen(src));
	if (!dest)
		return (NULL);
	start = dest;
	while (*src)
		*dest++ = *src++;
	*dest = '\0';
	return (start);
}

// char	*ft_strdup(const char *s)
// {
// 	char	*str;
// 	size_t	i;

// 	i = 0;
// 	if (!s)
// 		return (NULL);
// 	str = (char *)malloc((ft_strlen(s) + 1) * sizeof(char));
// 	if (!str)
// 		return (NULL);
// 	while (s[i])
// 	{
// 		str[i] = s[i];
// 		i++;
// 	}
// 	str[i] = '\0';
// 	return (str);
// }
//
// int	main(void)
// {
// 	//char	*str1 = "Oh wie schoen ist Panama";
// 	//char	*str2 = "wo";
// 	//
// 	printf("%s\n", ft_strdup(((void*)0)));
// 	return (0);
// }