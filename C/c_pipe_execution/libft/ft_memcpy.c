/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hreusing <hreusing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 11:27:14 by hreusing          #+#    #+#             */
/*   Updated: 2024/05/11 13:54:16 by hreusing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//was wenn n größer als src?

void	*ft_memcpy(void	*dest, void const *src, size_t n)
{
	void	*dest_ptr;

	dest_ptr = dest;
	if (!dest && !src)
		return (dest);
	while (n--)
		*(char *)dest++ = *(char *)src++;
	return (dest_ptr);
}
//
// void	*ft_memcpy(void *dest, const void *src, size_t n)
// {
// 	size_t	i;
// 	char	*d;
// 	char	*s;

// 	if (!src && !src)
// 		return (dest);
// 	d = (char *)dest;
// 	s = (char *)src;
// 	i = 0;
// 	while (i++ < n)
// 		*d++ = *s++;
// 	return (dest);
// }
//
// int	main(void)
// {
// 	char	src[] = "test basic du memcpy !";
// 	char	buff1[23];
//
// 	//printf("%i%s\n", 1, ft_memcpy(buff1, src, 22));
// 	//printf("%i%s", 2, memcpy(buff1, src, 22));
// 	printf("%i%s\n", 1, ft_memcpy("            ", ((void*)0), 17));
// 	printf("%i%s\n", 2, memcpy("            ", ((void*)0), 17));
//
// }
