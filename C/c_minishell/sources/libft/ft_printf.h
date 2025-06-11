/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbohme <pbohme@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 12:51:09 by pbohme            #+#    #+#             */
/*   Updated: 2024/05/11 18:02:30 by pbohme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stddef.h>
# include <stdarg.h>
# include <stdint.h>
# include "libft.h"

void	ft_hex_str(uintptr_t adr, char *buffer);
int		ft_print_digits(long n, int base, char spec);
int		ft_print_char(int c);
int		ft_count_hex(uintptr_t adr);
int		ft_format(va_list ap, char spec);
int		ft_print_str(char *str);
int		ft_print_void(void *ptr);
int		ft_printf(const char *str, ...);

#endif
