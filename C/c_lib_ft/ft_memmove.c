/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hreusing <hreusing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 11:00:43 by hreusing          #+#    #+#             */
/*   Updated: 2024/04/30 17:01:48 by hreusing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;
	size_t				i;

	if ((!src && !dest) || dest == src) 
		return (dest);
	d = (unsigned char *)dest;
	s = (const unsigned char *)src;
	i = 0;
	if (d > s)
	{
		while (n--)
			d[n] = s[n];
	}
	else
	{
		while (i < n)
		{
			d[i] = s[i];
			i++;
		}
	}
	return (dest);
}
/*
int	main(void)
{
	char	str[100] = "we have an elemenation";
	char	dest[20] = "";
	char b[0xF0];
 
 	printf("%i%s", 1, ft_memmove(((void*)0), b, 5));
	printf("%i%s", 2, memmove(((void*)0), b, 5));
	printf("%i%s\n", 1, ft_memmove(dest, str, 2));
	printf("%i%s", 2, memmove(dest, str, 2));
}*/
/*
int	main(void)
{
 	unsigned long src = 0xdeadbeef;
 	int size = sizeof(src);
 
 	unsigned long dst1;
 	unsigned long dst2;
 	printf("%i%s\n", 1, (char *)memmove(&dst1, &src, size));
 	printf("%i%s", 2, (char *)ft_memmove(&dst2, &src, size));

}*/
