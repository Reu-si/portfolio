/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hreusing <hreusing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 16:08:02 by hreusing          #+#    #+#             */
/*   Updated: 2024/05/14 16:00:57 by hreusing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_print_format(const char specifier, va_list ap)
{
	void	*ptr;

	if (specifier == 'c')
		return (ft_print_char(va_arg(ap, int)));
	else if (specifier == 's')
		return (ft_print_str(va_arg(ap, char *)));
	else if (specifier == 'p')
	{
		ptr = va_arg(ap, void *);
		if (ptr)
			return (ft_print_adress(ptr));
		return (ft_print_str("(nil)"));
	}
	else if (specifier == 'd' || specifier == 'i')
		return (ft_print_digit((long)va_arg(ap, int), 10, specifier));
	else if (specifier == 'u')
		return (ft_print_digit((long)va_arg(ap, unsigned int), 10, specifier));
	else if (specifier == 'x' || specifier == 'X')
		return (ft_print_digit((long)va_arg(ap, unsigned int), 16, specifier));
	else if (specifier == '%')
		return (ft_print_char('%'));
	else
		return (-1);
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		count;
	int		i;

	va_start(ap, format);
	count = 0;
	i = 0;
	while (format[i])
	{
		if (format[i] == '%')
		{
			i++;
			count += ft_print_format(format[i], ap);
		}
		else
			count += ft_print_char(format[i]);
		i++;
	}
	va_end(ap);
	return (count);
}

// int	main(void)
// {
// 	int	count;
// 	int	*ptr;	

// 	count = 345;
// 	ptr = &count;
// 	ft_printf("Hallo Adresse von count:  %p und %p\n", count, ptr);
// 	ft_printf(" %p %p ", ULONG_MAX, -ULONG_MAX);
// 	ft_printf(" %p %p %p ", -1, 0, 0);
// 	ft_printf(" %p %p ", LONG_MIN, LONG_MAX);
//  printf("\n %p %p ", ULONG_MAX, -ULONG_MAX);
// 	printf(" %p %p ", 0, 0);
// 	printf(" %p %p ", LONG_MIN, LONG_MAX);
// 	return (0);
// }
