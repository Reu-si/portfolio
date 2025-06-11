/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbohme <pbohme@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 14:26:58 by pbohme            #+#    #+#             */
/*   Updated: 2024/05/05 16:19:59 by pbohme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*p;

	i = 0;
	p = (unsigned char *)s;
	while (i < n)
	{
		p[i] = (char )c;
		i++;
	}
	return (s = p);
}

/*int	main(void)
{
	char	str[30] = "Hello, world!";
	int		c = 'X';
	size_t	n = 5;

	printf("Before memset: %s\n", str);
	ft_memset(str, c, n);
	printf("After ft_memset: %s\n", str);
	return (0);
}*/
