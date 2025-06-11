/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_void.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbohme <pbohme@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 17:03:04 by pbohme            #+#    #+#             */
/*   Updated: 2024/05/11 18:41:49 by pbohme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_count_hex(uintptr_t adr)
{
	int	i;

	if (adr == 0)
		return (1);
	i = 0;
	while (adr != 0)
	{
		adr /= 16;
		i++;
	}
	return (i);
}

void	ft_hex_str(uintptr_t adr, char *buffer)
{
	int		i;
	char	*digits;

	digits = "0123456789abcdef";
	if (adr == 0)
	{
		*buffer = '0';
		return ;
	}
	buffer[0] = '0';
	buffer[1] = 'x';
	i = 2;
	while (adr >= 16)
	{
		buffer[i] = digits[adr % 16];
		i++;
		adr = adr / 16;
	}
	buffer[i] = digits[adr % 16];
	i++;
	buffer[i] = '\0';
}

int	ft_nil(void)
{
	write (1, "(nil)", 5);
	return (5);
}

int	ft_print_void(void *ptr)
{
	char		buffer[20];
	uintptr_t	adr;
	int			count;
	int			i;

	if (!ptr)
		return (ft_nil());
	adr = (uintptr_t)ptr;
	count = ft_count_hex(adr);
	count += 2;
	ft_hex_str(adr, &buffer[0]);
	i = 0;
	while (buffer[i + 1] != '\0')
	{
		if (i < 2)
			ft_print_char(buffer[i]);
		i++;
	}
	while (i > 1)
	{
		ft_print_char(buffer[i]);
		i--;
	}
	return (count);
}
