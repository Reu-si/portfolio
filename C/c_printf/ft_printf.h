/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hreusing <hreusing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 14:46:03 by hreusing          #+#    #+#             */
/*   Updated: 2024/05/14 15:08:33 by hreusing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h> 
# include <stdlib.h>
# include <string.h>
# include <limits.h>   
# include <stddef.h>
# include <stdio.h>
# include <stdarg.h>
# include "libft.h"

int		ft_printf(const char *format, ...);

#endif