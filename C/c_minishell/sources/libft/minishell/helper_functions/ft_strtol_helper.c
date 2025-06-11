/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stol_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbohme <pbohme@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 14:52:59 by pbohme            #+#    #+#             */
/*   Updated: 2024/12/05 15:01:06 by pbohme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static const char	*skip_whitespace_and_sign(const char *s, int *neg)
{
	while (is_whitespace(*s))
		s++;
	*neg = 0;
	if (*s == '-')
	{
		*neg = 1;
		s++;
	}
	else if (*s == '+')
		s++;
	return (s);
}

static int	determine_base(const char **s, int base)
{
	if (base == 0)
	{
		base = 10;
		if (**s == '0')
		{
			base = 8;
			(*s)++;
			if (**s == 'x' || **s == 'X')
			{
				base = 16;
				(*s)++;
			}
		}
	}
	else if (base == 16 && **s == '0' && (*(*s + 1) == 'x' || *(*s + 1) == 'X'))
		*s += 2;
	return (base);
}

t_stol	*set_stl_struct(const char *nptr, int *base)
{
	t_stol	*new;

	new = malloc(sizeof(t_stol));
	if (!new)
		return (NULL);
	new->s = nptr;
	new->acc = 0;
	new->s = skip_whitespace_and_sign(new->s, &new->neg);
	*base = determine_base(&new->s, *base);
	new->cutoff = ULONG_MAX / *base;
	return (new);
}
