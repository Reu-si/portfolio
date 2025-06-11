/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbohme <pbohme@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 15:15:08 by pbohme            #+#    #+#             */
/*   Updated: 2024/05/05 17:13:44 by pbohme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void		*des;

	if (nmemb == 0 || size == 0)
		return (malloc (0));
	des = malloc(nmemb * size);
	if (!des)
		return (NULL);
	ft_bzero(des, nmemb * size);
	return (des);
}

/*int	main(void)
{
	int	*arr;
	int	nmemb = 0;
	int	i;
	size_t	size = sizeof(int);

	arr = (int *)ft_calloc(nmemb, size);
	if (arr == NULL)
		return (1);
	i = 0;
	while (i < nmemb)
	{
		arr[i] = i + 1;
		printf("%d\n", arr[i]);
		i++;
	}
	free (arr);
	return (0);
}*/
