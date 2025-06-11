/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hreusing <hreusing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 16:15:29 by hreusing          #+#    #+#             */
/*   Updated: 2024/05/07 15:50:42 by hreusing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char	*h;
	char	*n;
	size_t	l;

	if (*needle == 0)
		return ((char *)haystack);
	n = (char *)needle;
	while (*haystack && len > 0)
	{
		h = (char *)haystack;
		l = len;
		while (*haystack && *needle && *haystack == *needle && len-- > 0)
		{
			haystack++;
			needle++;
		}
		if (!*needle)
			return (h);
		haystack = ++h;
		needle = n;
		len = --l;
	}
	return (NULL);
}

// int	main(void)
// {
// 	//char	*str1 = "Oh wie schoen ist Panama";
// 	//char	*str2 = "wo";
// 	//
// 	char	*empty = (char *)"";
// 	//printf("%s\n", ft_strnstr("lorem ipsum dolor sit amet", "dolor", 15));
// 	//printf("%s\n", ft_strnstr(empty, "", 0));
// 	printf("%s\n", ft_strnstr(empty, "12345", 5));
// 	return (0);
// }
