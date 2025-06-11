/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stol.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbohme <pbohme@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 18:02:45 by pbohme            #+#    #+#             */
/*   Updated: 2024/12/08 16:44:08 by pbohme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	get_digit(char c, int base)
{
	int	digit;

	if (ft_isdigit(c))
		digit = c - '0';
	else if (ft_isalpha(c))
	{
		if (isupper(c))
			digit = c - 'A' + 10;
		else
			digit = c - 'a' + 10;
	}
	else 
		return (-1);
	if (digit >= base)
		return (-1);
	return (digit);
}

static long	handle_result(unsigned long acc, int neg)
{
	if (neg)
	{
		if (acc > (unsigned long)LONG_MIN)
		{
			errno = ERANGE;
			return (LONG_MIN);
		}
		return (-(long)acc);
	}
	if (acc > (unsigned long)LONG_MAX)
	{
		errno = ERANGE;
		return (LONG_MAX);
	}
	return ((long)acc);
}

long	ft_stol(const char *nptr, char **endptr, int base)
{
	t_stol	*new;
	int		digit;
	long	result;

	new = set_stl_struct (nptr, &base);
	digit = get_digit(*(new->s), base);
	while (digit >= 0)
	{
		if (new->acc > new->cutoff || (new->acc == new->cutoff 
				&& (unsigned long)digit > ULONG_MAX % base))
		{
			new->acc = ULLONG_MAX;
			errno = ERANGE;
			break ;
		}
		new->acc = new->acc * base + digit;
		(new->s)++;
		digit = get_digit(*(new->s), base);
	}
	if (endptr)
		*endptr = (char *)(new->s);
	result = handle_result(new->acc, new->neg);
	free (new);
	return (result);
}
