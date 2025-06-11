/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_types.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hreusing <hreusing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 12:26:35 by hreusing          #+#    #+#             */
/*   Updated: 2024/08/29 13:20:05 by hreusing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

int	ft_calc_rotate_ab(t_stack *stack_a, t_stack *stack_b)
{
	int		i;
	t_stack	*tmp;

	tmp = stack_a;
	i = ft_case_rrarrb(stack_a, stack_b, stack_a->nbr);
	while (tmp)
	{
		if (i > ft_case_rarb(stack_a, stack_b, tmp->nbr))
			i = ft_case_rarb(stack_a, stack_b, tmp->nbr);
		if (i > ft_case_rrarrb(stack_a, stack_b, tmp->nbr))
			i = ft_case_rrarrb(stack_a, stack_b, tmp->nbr);
		if (i > ft_case_rarrb(stack_a, stack_b, tmp->nbr))
			i = ft_case_rarrb(stack_a, stack_b, tmp->nbr);
		if (i > ft_case_rrarb(stack_a, stack_b, tmp->nbr))
			i = ft_case_rrarb(stack_a, stack_b, tmp->nbr);
		tmp = tmp->next;
	}
	return (i);
}

int	ft_calc_rotate_ba(t_stack *stack_a, t_stack *stack_b)
{
	int		i;
	t_stack	*tmp;

	tmp = stack_b;
	i = ft_case_rrarrb_a(stack_a, stack_b, stack_b->nbr);
	while (tmp)
	{
		if (i > ft_case_rarb_a(stack_a, stack_b, tmp->nbr))
			i = ft_case_rarb_a(stack_a, stack_b, tmp->nbr);
		if (i > ft_case_rrarrb_a(stack_a, stack_b, tmp->nbr))
			i = ft_case_rrarrb_a(stack_a, stack_b, tmp->nbr);
		if (i > ft_case_rarrb_a(stack_a, stack_b, tmp->nbr))
			i = ft_case_rarrb_a(stack_a, stack_b, tmp->nbr);
		if (i > ft_case_rrarb_a(stack_a, stack_b, tmp->nbr))
			i = ft_case_rrarb_a(stack_a, stack_b, tmp->nbr);
		tmp = tmp->next;
	}
	return (i);
}
