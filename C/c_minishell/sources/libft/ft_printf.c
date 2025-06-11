/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbohme <pbohme@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 12:54:12 by pbohme            #+#    #+#             */
/*   Updated: 2024/05/14 11:53:29 by pbohme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_char(int c)
{
	char	k;

	k = (char )c;
	write (1, &k, 1);
	return (1);
}

int	ft_format(va_list ap, char spec)
{
	int	len;

	len = 0;
	if (spec == 'c')
		len += ft_print_char(va_arg(ap, int));
	else if (spec == 's')
		len += ft_print_str(va_arg(ap, char *));
	else if (spec == 'p')
		len += ft_print_void(va_arg(ap, void *));
	else if (spec == 'i' || spec == 'd')
		len += ft_print_digits((long)(va_arg(ap, int)), 10, spec);
	else if (spec == 'u')
		len += ft_print_digits((long)(va_arg(ap, unsigned int)), 10, spec);
	else if (spec == 'x')
		len += ft_print_digits((long)(va_arg(ap, unsigned int)), 16, spec);
	else if (spec == 'X')
		len += ft_print_digits((long)(va_arg(ap, unsigned int)), 16, spec);
	else if (spec == '%')
		len += ft_print_char('%');
	return (len);
}

int	ft_printf(const char *str, ...)
{
	va_list	ap;
	int		i;
	int		count;

	if (!str)
		return (-1);
	va_start(ap, str);
	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '%')
		{
			count += ft_format(ap, str[i + 1]);
			i++;
		}
		else
			count += ft_print_char(str[i]);
		i++;
	}
	va_end (ap);
	return (count);
}
