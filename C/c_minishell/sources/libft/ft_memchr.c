/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbohme <pbohme@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 12:21:14 by pbohme            #+#    #+#             */
/*   Updated: 2024/05/05 16:59:17 by pbohme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t		i;
	char		*p;

	p = (void *)s;
	i = 0;
	while (i < n)
	{
		if (p[i] == (char )c)
			return (&p[i]);
		i++;
	}
	return (NULL);
}

/*int	main(void)
{
	char	str[] = "Hello world, nice to see u!";
	//char	c = 'a';
	char	*des;
	//size_t	t = 10;

	des = ft_memchr(str, 2 + 256, 3);
	printf("%s\n", des);
	return (0);
}*/
