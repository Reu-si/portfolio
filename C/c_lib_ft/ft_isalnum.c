/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hreusing <hreusing@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 10:54:02 by hreusing          #+#    #+#             */
/*   Updated: 2024/04/25 10:56:23 by hreusing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalnum(int argument)
{
	if (argument >= 48 && argument <= 57)
		return (1);
	else if (argument >= 65 && argument <= 90)
		return (3);
	else if (argument >= 97 && argument <= 122)
		return (2);
	else
		return (0);
}
