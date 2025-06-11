/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hreusing <hreusing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 11:15:17 by hreusing          #+#    #+#             */
/*   Updated: 2024/04/25 14:44:11 by hreusing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *str, size_t n)
{
	while (n > 0)
	{
		*(unsigned char *)str++ = '\0';
		n--;
	}
}
/* 
#include <stdio.h>
#include <string.h>
int     main(void)
{
    char    str[100] = "we have an elimination right now";

    printf("%s", ft_bzero(str, 10));
} */