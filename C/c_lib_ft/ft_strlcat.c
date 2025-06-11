/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hreusing <hreusing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 14:35:13 by hreusing          #+#    #+#             */
/*   Updated: 2024/05/02 18:28:57 by hreusing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t n)
{
	size_t	i;
	size_t	dlen;
	size_t	slen;
	size_t	tlen;

	i = 0;
	dlen = ft_strlen(dest);
	slen = ft_strlen(src);
	tlen = dlen + slen;
	if (n == 0 || dlen >= n)
		return (n + slen);
	while (src[i] && dlen + i < n - 1)
	{
		dest[dlen + i] = src[i];
		i++;
	}
	dest[dlen + i] = '\0';
	return (tlen);
}

/* 
int	main(void)
{
	char	dest1[10] = "Hallo ";
	char	src[20] = " Welt islsjdncfndneh";
	unsigned int	n;
	int	a;

	n = 10;
	a = ft_strlcat(dest1, src, n);
	printf("%i\n%s\n", a, dest1);
	return (0);
} */
