/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hreusing <hreusing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 14:46:03 by hreusing          #+#    #+#             */
/*   Updated: 2024/05/14 16:01:58 by hreusing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h> 
# include <stdlib.h>
# include <string.h>
# include <limits.h>   
# include <stddef.h>
# include <stdio.h>
# include <stdarg.h>

int		ft_print_str(char *str);
int		ft_print_digit(long n, int base, char specifier);
int		ft_print_char(char c);
int		ft_print_adress(void *format);
size_t	ft_strlen(const char *str);

#endif