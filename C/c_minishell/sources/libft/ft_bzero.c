/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbohme <pbohme@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 14:47:09 by pbohme            #+#    #+#             */
/*   Updated: 2024/05/01 15:21:16 by pbohme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdio.h>

void	ft_bzero(void *s, size_t n)
{
	size_t			i;

	i = 0;
	while (i < n)
	{
		((unsigned char *)s)[i] = '\0';
		i++;
	}
}

/*int	main(void)
{
	int 	str[7] = {12, 5, 4, 4, 5, 12, 34};
	//char	str[] = "helloagain";
	size_t	n = 16;
	int	i;

	i = 0;
        while (i < 7)
                printf("%i\n", str[i++]);
	ft_bzero(str, n);
	i = 0;
	while (i < 7)
		printf("%i\n", str[i++]);
	return (0);
}*/
