/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hreusing <hreusing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 12:26:02 by hreusing          #+#    #+#             */
/*   Updated: 2024/08/29 12:26:04 by hreusing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

int	ft_apply_rrarrb(t_stack **stack_a, t_stack **stack_b, int num, char s)
{
	if (s == 'b')
	{
		while ((*stack_a)->nbr != num && ft_find_place_in_b(*stack_b, num) > 0)
			ft_rrr(stack_a, stack_b);
		while ((*stack_a)->nbr != num)
			ft_rra(stack_a);
		while (ft_find_place_in_b(*stack_b, num) > 0)
			ft_rrb(stack_b);
		ft_pb(stack_a, stack_b);
	}
	else
	{
		while ((*stack_b)->nbr != num && ft_find_place_in_a(*stack_a, num) > 0)
			ft_rrr(stack_a, stack_b);
		while ((*stack_b)->nbr != num)
			ft_rrb(stack_b);
		while (ft_find_place_in_a(*stack_a, num) > 0)
			ft_rra(stack_a);
		ft_pa(stack_a, stack_b);
	}
	return (-1);
}

int	ft_apply_rarb(t_stack **stack_a, t_stack **stack_b, int num, char s)
{
	if (s == 'b')
	{
		while ((*stack_a)->nbr != num && ft_find_place_in_b(*stack_b, num) > 0)
			ft_rr(stack_a, stack_b);
		while ((*stack_a)->nbr != num)
			ft_ra(stack_a);
		while (ft_find_place_in_b(*stack_b, num) > 0)
			ft_rb(stack_b);
		ft_pb(stack_a, stack_b);
	}
	else
	{
		while ((*stack_b)->nbr != num && ft_find_place_in_a(*stack_a, num) > 0)
			ft_rr(stack_a, stack_b);
		while ((*stack_b)->nbr != num)
			ft_rb(stack_b);
		while (ft_find_place_in_a(*stack_a, num) > 0)
			ft_ra(stack_a);
		ft_pa(stack_a, stack_b);
	}
	return (-1);
}

int	ft_apply_rarrb(t_stack **stack_a, t_stack **stack_b, int num, char s)
{
	if (s == 'b')
	{
		while ((*stack_a)->nbr != num)
			ft_ra(stack_a);
		while (ft_find_place_in_b(*stack_b, num) > 0)
			ft_rrb(stack_b);
		ft_pb(stack_a, stack_b);
	}
	else
	{
		while (ft_find_place_in_a(*stack_a, num) > 0)
			ft_ra(stack_a);
		while ((*stack_b)->nbr != num)
			ft_rrb(stack_b);
		ft_pa(stack_a, stack_b);
	}
	return (-1);
}

int	ft_apply_rrarb(t_stack **stack_a, t_stack **stack_b, int num, char s)
{
	if (s == 'b')
	{
		while ((*stack_a)->nbr != num)
			ft_rra(stack_a);
		while (ft_find_place_in_b(*stack_b, num) > 0)
			ft_rb(stack_b);
		ft_pb(stack_a, stack_b);
	}
	else
	{
		while (ft_find_place_in_a(*stack_a, num) > 0)
			ft_rra(stack_a);
		while ((*stack_b)->nbr != num)
			ft_rb(stack_b);
		ft_pa(stack_a, stack_b);
	}
	return (-1);
}
