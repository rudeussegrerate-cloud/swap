/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrandri2 <hrandri2@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 00:52:34 by hrandri2          #+#    #+#             */
/*   Updated: 2026/04/11 00:54:18 by hrandri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

void	slow_bring_to_top(t_stack_node **stack, t_stack_node *node,
							char name, t_count *count)
{
	while (*stack != node)
	{
		if (name == 'a')
			ra(stack, count);
		else
			rb(stack, count);
		set_current_position(*stack);
	}
}

static void	fast_bring_to_top(t_stack_node **stack, t_stack_node *node,
							char name, t_count *count)
{
	set_current_position(*stack);
	while (*stack != node)
	{
		if (node->above_median)
		{
			if (name == 'a')
				ra(stack, count);
			else
				rb(stack, count);
		}
		else
		{
			if (name == 'a')
				rra(stack, count);
			else
				rrb(stack, count);
		}
		set_current_position(*stack);
	}
}

void	move_slow(t_stack_node **a, t_stack_node **b, t_count *count)
{
	t_stack_node	*cheapest;
	t_stack_node	*target;

	set_current_position(*a);
	set_current_position(*b);
	cheapest = find_cheapest_limited(*a, *b, 0);
	target = find_insert_position(*a, cheapest->value);
	slow_bring_to_top(b, cheapest, 'b', count);
	slow_bring_to_top(a, target, 'a', count);
	pa(a, b, count);
}

void	move_fast(t_stack_node **a, t_stack_node **b,
					t_count *count, int percent)
{
	t_stack_node	*cheapest;
	t_stack_node	*target;

	set_current_position(*a);
	set_current_position(*b);
	cheapest = find_cheapest_limited(*a, *b, percent);
	target = find_insert_position(*a, cheapest->value);
	fast_bring_to_top(b, cheapest, 'b', count);
	fast_bring_to_top(a, target, 'a', count);
	pa(a, b, count);
}
