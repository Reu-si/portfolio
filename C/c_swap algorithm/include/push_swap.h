/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hreusing <hreusing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 12:25:54 by hreusing          #+#    #+#             */
/*   Updated: 2024/08/29 13:02:41 by hreusing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "/home/hreusing/libft/libft.h"
//# include "../../../libft/libft.h"

typedef struct s_stack
{
	long long int	nbr;
	struct s_stack	*next;
}	t_stack;

void	ft_stackadd_back(t_stack **lst, t_stack *new);
void	ft_stack_add_front(t_stack **stack, t_stack *new);
t_stack	*ft_stacknew(int content, t_stack **stack_a);
int		ft_stack_size(t_stack *lst);
t_stack	*ft_stack_last(t_stack *lst);
int		ft_stack_min(t_stack *stack);
int		ft_stack_max(t_stack *stack);

int		ft_isnum(char *num);
int		ft_check_dup(t_stack *stack_a);
int		ft_check_sorted(t_stack *stack_a);
void	ft_check_string_args(char **argv, t_stack **stack_a);
int		ft_check_args(int argc, char **argv, t_stack **stack_a);

void	ft_free_arr(char **arr);
void	ft_free(t_stack **lst);
void	ft_free_str_stack(t_stack **stack, char	**arr);

void	ft_error(char *message, t_stack **stack_a);
int		ft_atoi2(char *str, t_stack **stack_a, char **arr);

int		ft_find_index(t_stack *stack, int nbr_push);
int		ft_find_place_in_b(t_stack *stack_b, int nbr_to_push);
int		ft_find_place_in_a(t_stack *stack_a, int nbr_to_push);

int		ft_case_rrarrb(t_stack *a, t_stack *b, int num);
int		ft_case_rarb(t_stack *a, t_stack *b, int num);
int		ft_case_rarrb(t_stack *a, t_stack *b, int num);
int		ft_case_rrarb(t_stack *a, t_stack *b, int num);

int		ft_case_rrarrb_a(t_stack *a, t_stack *b, int num);
int		ft_case_rarb_a(t_stack *a, t_stack *b, int num);
int		ft_case_rarrb_a(t_stack *a, t_stack *b, int num);
int		ft_case_rrarb_a(t_stack *a, t_stack *b, int num);

void	ft_sa(t_stack **stack_a);
void	ft_sb(t_stack **stack_b);
void	ft_ss(t_stack **stack_a, t_stack **stack_b);
void	ft_pa(t_stack **stack_a, t_stack **stack_b);
void	ft_pb(t_stack **stack_a, t_stack **stack_b);
void	ft_ra(t_stack **stack_a);
void	ft_rb(t_stack **stack_b);
void	ft_rr(t_stack **stack_a, t_stack **stack_b);
void	ft_rra(t_stack **stack_a);
void	ft_rrb(t_stack **stack_b);
void	ft_rrr_helper(t_stack **stack_b);
void	ft_rrr(t_stack **stack_a, t_stack **stack_b);

int		ft_calc_rotate_ab(t_stack *stack_a, t_stack *stack_b);
int		ft_calc_rotate_ba(t_stack *stack_a, t_stack *stack_b);

int		ft_apply_rrarrb(t_stack **stack_a, t_stack **stack_b, int num, char s);
int		ft_apply_rarb(t_stack **stack_a, t_stack **stack_b, int num, char s);
int		ft_apply_rarrb(t_stack **stack_a, t_stack **stack_b, int num, char s);
int		ft_apply_rrarb(t_stack **stack_a, t_stack **stack_b, int num, char s);

void	ft_sort_three(t_stack **stack);
void	ft_sort_b_till_a_has_3(t_stack **stack_a, t_stack **stack_b);
t_stack	*ft_sort_b(t_stack **stack_a);
t_stack	**ft_sort_a(t_stack **stack_a, t_stack **stack_b);
void	ft_sort(t_stack **stack_a);

#endif