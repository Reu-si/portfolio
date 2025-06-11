/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbohme <pbohme@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 18:33:42 by pbohme            #+#    #+#             */
/*   Updated: 2024/05/05 16:26:52 by pbohme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	length;

	if (size == 0)
	{
		i = 0;
		while (src[i])
			i++;
		return (i);
	}
	i = 0;
	while (i < size - 1 && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	length = 0;
	while (src[length] != '\0')
		length++;
	return (length);
}

/*int	main(void)
{
	char	dest[20];
	char	src[] = "Helloo";
	size_t	size;

	size = 3;
	printf("%d\n", ft_strlcpy(dest, src, size));
	return (0);
}*/
