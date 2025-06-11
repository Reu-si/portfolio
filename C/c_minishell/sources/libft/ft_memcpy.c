/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbohme <pbohme@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 11:47:46 by pbohme            #+#    #+#             */
/*   Updated: 2024/05/05 15:29:30 by pbohme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char		*d;
	const char	*s;

	if ((dest == src) || n == 0)
		return (dest);
	d = (char *)dest;
	s = (const char *)src;
	while (n--)
		d[n] = s[n];
	return (dest);
}

/*int	main(void)
{
	char	dest[] = "Hellooworld";
	char	src[] = "banana";
	size_t	n = 6;

	printf("before : %s\n", dest);
	ft_memcpy(dest, src, n);
	printf("after : %s\n", dest);
	return (0);
}*/
