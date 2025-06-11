/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hreusing <hreusing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 16:03:10 by hreusing          #+#    #+#             */
/*   Updated: 2024/05/07 13:26:44 by hreusing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	if (n == 0)
		return (0);
	while (*str1 && *str2 && n > 1
		&& *(unsigned char *)str1 == *(unsigned char *)str2)
	{
		str1++;
		str2++;
		n--;
	}
	return (*(unsigned char *)str1 - *(unsigned char *)str2);
}
/* 
int	main(void)
{
	char	*s1 = "ABC";
	char	*s2 = "A2";
	
	printf("%i", ft_strncmp("test\200", "test\0", 6));
} */