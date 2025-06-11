/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_digit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hreusing <hreusing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 18:41:50 by hreusing          #+#    #+#             */
/*   Updated: 2024/06/27 16:18:33 by hreusing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_digit(long n, int base, char specifier)
{
	int		count;
	char	*symbols;

	if (specifier == 'X')
		symbols = "0123456789ABCDEF";
	else
		symbols = "0123456789abcdef";
	if (n < 0)
	{
		ft_print_char('-');
		return ((ft_print_digit(-n, base, specifier)) + 1);
	}
	else if (n < base)
		return (ft_print_char (symbols[n]));
	else
	{
		count = ft_print_digit(n / base, base, specifier);
		return (count + ft_print_digit(n % base, base, specifier));
	}
}
