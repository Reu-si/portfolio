/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbohme <pbohme@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 14:55:44 by pbohme            #+#    #+#             */
/*   Updated: 2024/05/03 17:20:41 by pbohme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*m;
	unsigned char	*p;

	m = (unsigned char *)s1;
	p = (unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (m[i] != p[i])
			return (m[i] - p[i]);
		i++;
	}
	return (0);
}

/*int	main(void)
{
	//const char	s1[] = "hellooooooooo";
	//const char	s2[] = "aelloaaa";
	char s2[] = {0, 0, 127, 0};
	char s3[] = {0, 0, 42, 0};
	size_t	n = 4;

	printf("%i\n", ft_memcmp(s2, s3, n));
	return (0);
}*/
