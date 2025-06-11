/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbohme <pbohme@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 21:00:54 by pbohme            #+#    #+#             */
/*   Updated: 2024/05/03 16:08:41 by pbohme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*size_t	ft_strlcat(char *dst, char *src, size_t size);

int	main(void)
{
	size_t	size;
//	char			src[] = "Hello";
	char			dest[50] = "Welcome";

	size = -1;
	printf("%zu", ft_strlcat(dest, "CCCCCAAAAAAAAA", size));
	return (0);
}*/

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dl;
	size_t	sl;
	size_t	i;

	dl = 0;
	sl = 0;
	while (dl < size && dst[dl])
		dl++;
	while (src[sl])
		sl++;
	i = 0;
	while ((dl + i) + 1 < size && src[i])
	{
		dst[dl + i] = src[i];
		i++;
	}
	if (dl < size)
		dst[dl + i] = '\0';
	return (dl + sl);
}

/*size_t	ft_strlcat(char *dst, char *src, size_t size)
{
	size_t	dl;
	size_t	tl;
	size_t	i;

	if ((!dst || !src) && !size)
		return (0);
	dl = 0;
	while (dst[dl] && dl < size)
		dl++;
	if (dl < size)
		tl = dl + size;
	else
		return (ft_strlen(src) + size);
	i = 0;
	while (src[i] && dl + 1 < size)
	{
		dst[dl + i] = src[i];
		i++;
	}
	dst[dl + i] = '\0';
	return (tl);
}*/

/*{
	size_t	i;
	size_t	j;
	size_t	k;

	if (size == 0)
		return (ft_strlen(src));
	i = 0;
	k = 0;
	while (*dst)
	{
		dst++;
		i++;
		k++;
	}
	j = 0;
	while (src[j++])
		i++;
	while (k < size && *src)
	{
		*dst++ = *src++;
		k++;
	}
	*dst = '\0';
	return (i);
}*/
