/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hreusing <hreusing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 18:39:46 by hreusing          #+#    #+#             */
/*   Updated: 2024/06/27 16:18:37 by hreusing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_str(char *str)
{
	int	count;

	if (!str)
		return (ft_print_str("(null)"));
	count = 0;
	while (*str)
	{
		ft_print_char((int)*str);
		count++;
		str++;
	}
	return (count);
}
