/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrandri2 <hrandri2@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 20:09:54 by hrandri2          #+#    #+#             */
/*   Updated: 2026/04/08 01:40:50 by hrandri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

void	rotate_both(t_stack_node **a,
						t_stack_node **b,
						t_stack_node *cheapest_node,
						t_count *count)
{
	while (*a != cheapest_node->target_node
		&& *b != cheapest_node)
		rr(a, b, count);
	set_current_position(*a);
	set_current_position(*b);
}

void	reverse_rotate_both(t_stack_node **a,
								t_stack_node **b,
								t_stack_node *cheapest_node,
								t_count *count)
{
	while (*a != cheapest_node->target_node
		&& *b != cheapest_node)
		rrr(a, b, count);
	set_current_position(*a);
	set_current_position(*b);
}

void	finish_rotation(t_stack_node **stack,
						t_stack_node *top_node,
						char stack_name,
						t_count *count)
{
	while (*stack != top_node)
	{
		if (stack_name == 'a')
		{
			if (top_node->above_median)
				ra(stack, count);
			else
				rra(stack, count);
		}
		else if (stack_name == 'b')
		{
			if (top_node->above_median)
				rb(stack, count);
			else
				rrb(stack, count);
		}
	}
}
