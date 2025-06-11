/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hreusing <hreusing@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 10:54:16 by hreusing          #+#    #+#             */
/*   Updated: 2024/04/25 10:56:01 by hreusing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// was ist mit zb. hexadezimalcode 
// (zb argument = 0x7c bis 0x82 --> 0x80 
// ist nicht darstellbar in ascii)
int	ft_isascii(int argument)
{
	if (argument >= 0 && argument <= 127)
		return (1);
	else
		return (0);
}
