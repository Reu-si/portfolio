/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hreusing <hreusing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 12:26:42 by hreusing          #+#    #+#             */
/*   Updated: 2024/08/29 13:22:49 by hreusing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

void	ft_sort_three(t_stack **stack)
{
	if (ft_stack_min(*stack) == (*stack)->nbr)
	{
		ft_rra(stack);
		ft_sa(stack);
	}
	else if (ft_stack_max(*stack) == (*stack)->nbr)
	{
		ft_ra(stack);
		if (!ft_check_sorted(*stack))
			ft_sa(stack);
	}
	else
	{
		if (ft_find_index(*stack, ft_stack_max(*stack)) == 1)
			ft_rra(stack);
		else
			ft_sa(stack);
	}
}

void	ft_sort_b_till_a_has_3(t_stack **stack_a, t_stack **stack_b)
{
	int		i;
	t_stack	*tmp;

	while (ft_stack_size(*stack_a) > 3 && !ft_check_sorted(*stack_a))
	{
		tmp = *stack_a;
		i = ft_calc_rotate_ab(*stack_a, *stack_b);
		while (i >= 0)
		{
			if (i == ft_case_rarb(*stack_a, *stack_b, tmp->nbr))
				i = ft_apply_rarb(stack_a, stack_b, tmp->nbr, 'b');
			else if (i == ft_case_rrarrb(*stack_a, *stack_b, tmp->nbr))
				i = ft_apply_rrarrb(stack_a, stack_b, tmp->nbr, 'b');
			else if (i == ft_case_rarrb(*stack_a, *stack_b, tmp->nbr))
				i = ft_apply_rarrb(stack_a, stack_b, tmp->nbr, 'b');
			else if (i == ft_case_rrarb(*stack_a, *stack_b, tmp->nbr))
				i = ft_apply_rrarb(stack_a, stack_b, tmp->nbr, 'b');
			else
				tmp = tmp->next;
		}
	}
}

t_stack	*ft_sort_b(t_stack **stack_a)
{
	t_stack	*stack_b;

	stack_b = NULL;
	if (ft_stack_size(*stack_a) > 3 && !ft_check_sorted(*stack_a))
		ft_pb(stack_a, &stack_b);
	if (ft_stack_size(*stack_a) > 3 && !ft_check_sorted(*stack_a))
		ft_pb(stack_a, &stack_b);
	if (ft_stack_size(*stack_a) > 3 && !ft_check_sorted(*stack_a))
		ft_sort_b_till_a_has_3(stack_a, &stack_b);
	if (!ft_check_sorted(*stack_a))
		ft_sort_three(stack_a);
	return (stack_b);
}

t_stack	**ft_sort_a(t_stack **stack_a, t_stack **stack_b)
{
	int		i;
	t_stack	*tmp;

	while (*stack_b)
	{
		tmp = *stack_b;
		i = ft_calc_rotate_ba(*stack_a, *stack_b);
		while (i >= 0)
		{
			if (i == ft_case_rarb_a(*stack_a, *stack_b, tmp->nbr))
				i = ft_apply_rarb(stack_a, stack_b, tmp->nbr, 'a');
			else if (i == ft_case_rarrb_a(*stack_a, *stack_b, tmp->nbr))
				i = ft_apply_rarrb(stack_a, stack_b, tmp->nbr, 'a');
			else if (i == ft_case_rrarrb_a(*stack_a, *stack_b, tmp->nbr))
				i = ft_apply_rrarrb(stack_a, stack_b, tmp->nbr, 'a');
			else if (i == ft_case_rrarb_a(*stack_a, *stack_b, tmp->nbr))
				i = ft_apply_rrarb(stack_a, stack_b, tmp->nbr, 'a');
			else
				tmp = tmp->next;
		}
	}
	return (stack_a);
}

void	ft_sort(t_stack **stack_a)
{
	t_stack	*stack_b;
	int		i;

	stack_b = NULL;
	if (ft_stack_size(*stack_a) == 2)
		ft_sa(stack_a);
	else
	{
		stack_b = ft_sort_b(stack_a);
		stack_a = ft_sort_a(stack_a, &stack_b);
		i = ft_find_index(*stack_a, ft_stack_min(*stack_a));
		if (i < ft_stack_size(*stack_a) - i)
		{
			while ((*stack_a)->nbr != ft_stack_min(*stack_a))
				ft_ra(stack_a);
		}
		else
		{
			while ((*stack_a)->nbr != ft_stack_min(*stack_a))
				ft_rra(stack_a);
		}
	}
}
