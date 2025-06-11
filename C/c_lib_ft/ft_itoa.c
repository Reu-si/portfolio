/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hreusing <hreusing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 11:52:08 by hreusing          #+#    #+#             */
/*   Updated: 2024/05/11 13:56:49 by hreusing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	ft_numbercount(int n)
{
	int	count;

	count = 1;
	if (n < 0)
		count++;
	while (n > 9 || n < -9)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

static char	*str_new(size_t n)
{
	char	*str;

	str = (char *)malloc(sizeof(char) * (n + 1));
	if (!str)
		return (NULL);
	return (str);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		count;

	count = ft_numbercount(n);
	str = str_new(count);
	if (!str)
		return (NULL);
	str[count--] = '\0';
	if (n < 0)
	{
		str[0] = '-';
		if (n == -2147483648)
		{
			str[count--] = '8';
			n /= 10;
		}
		n *= -1;
	}
	while (n > 9)
	{
		str[count--] = (n % 10) + '0';
		n = n / 10;
	}
	str[count] = n + '0';
	return (str);
}

// int	main(void)
// {
// 	printf("%s\n", ft_itoa(0));
// }
