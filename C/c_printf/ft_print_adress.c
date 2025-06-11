/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_adress.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hreusing <hreusing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 18:42:01 by hreusing          #+#    #+#             */
/*   Updated: 2024/05/14 15:56:35 by hreusing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_rec_adress(unsigned long n, const char *base)
{
	int				count;
	unsigned int	base_len;

	count = 0;
	base_len = ft_strlen(base);
	if (n > (base_len - 1))
		count += ft_rec_adress(n / base_len, base);
	count += ft_print_char(*(base + (n % base_len)));
	return (count);
}

int	ft_print_adress(void *format)
{
	unsigned long	n;
	const char		*base;
	int				count;

	n = (unsigned long)format;
	base = "0123456789abcdef";
	count = ft_print_str("0x");
	count += ft_rec_adress(n, base);
	return (count);
}
