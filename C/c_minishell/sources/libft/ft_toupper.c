/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbohme <pbohme@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:39:54 by pbohme            #+#    #+#             */
/*   Updated: 2024/04/19 16:08:34 by pbohme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>

int	ft_toupper(int c)
{
	if (!(c >= 97 && c <= 122))
		return (c);
	return (c - 32);
}

/*int	main(void)
{
	unsigned char	c;

	c = 'z';
	printf("%i", ft_toupper(c));
	return (0);
}*/
