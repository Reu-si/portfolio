/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hreusing <hreusing@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 10:59:08 by hreusing          #+#    #+#             */
/*   Updated: 2024/04/25 11:00:18 by hreusing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int c, size_t n)
{
	void	*str_ptr;

	str_ptr = str;
	while (n > 0)
	{
		*(unsigned char *)str++ = (unsigned char)c;
		n--;
	}
	return (str_ptr);
}
/*
#include <stdio.h>
#include <string.h>
int     main(void)
{
    char    str[100] = "we have an elimination right now";

    printf("%s", ft_memset(str, '5', 10));
}*/
