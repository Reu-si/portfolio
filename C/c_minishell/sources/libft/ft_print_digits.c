/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_digits.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbohme <pbohme@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 18:46:45 by pbohme            #+#    #+#             */
/*   Updated: 2024/05/11 17:30:10 by pbohme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*int	ft_digits(int n)
{
	int	temp;
	int	digits;

	temp = n;
	digits = 0;
	while (n != 0)
	{
		digits++;
		n /= 10;
	}
	if (temp < 0)
		return (digits + 1);
	return (digits);
}*/

int	ft_print_digits(long n, int base, char spec)
{
	int		count;
	char	*str;

	str = "0123456789abcdef";
	if (spec == 'X')
		str = "0123456789ABCDEF";
	if (n < 0)
	{
		write (1, "-", 1);
		return (ft_print_digits(-n, base, spec) + 1);
	}
	if (n < base)
		return (ft_print_char(str[n]));
	else
	{
		count = ft_print_digits(n / base, base, spec);
		return (count + ft_print_digits(n % base, base, spec));
	}
}

/*{
	char	nu;
	int		len;

	if (n == -2147483648)
	{
		write (1, "-2147483648", 11);
		return (11);
	}
	len = ft_digits(n);
	if (n < 0)
	{
		write (1, "-", 1);
		n = -n;
	}
	if (n >= 10)
	{
		ft_print_int(n / 10);
	}
	nu = (n % 10) + '0';
	write (1, &nu, 1);
	return (len);
}*/

/*int	main(void)
{
	int	n;
	int	count;

	n = -2;
	count = ft_print_int(n);
	printf("\n");
	printf("%i", count);
	return (0);
}*/
