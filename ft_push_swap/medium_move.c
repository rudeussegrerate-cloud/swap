/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   medium_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrandri2 <hrandri2@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 00:37:14 by hrandri2          #+#    #+#             */
/*   Updated: 2026/04/11 00:42:05 by hrandri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

void	move_back_fast(t_stack_node **a, t_stack_node **b, t_count *count)
{
	t_stack_node	*cheapest;

	while (*b)
	{
		init_nodes(*a, *b);
		cheapest = return_cheapest(*b);
		if (!cheapest)
			break ;
		if (cheapest->above_median
			&& cheapest->target_node->above_median)
			while (*a != cheapest->target_node && *b != cheapest)
				rr(a, b, count);
		else if (!cheapest->above_median
			&& !cheapest->target_node->above_median)
			while (*a != cheapest->target_node && *b != cheapest)
				rrr(a, b, count);
		finish_rotation(b, cheapest, 'b', count);
		finish_rotation(a, cheapest->target_node, 'a', count);
		pa(a, b, count);
	}
}

static void	slow_bring_to_top(t_stack_node **stack, t_stack_node *node,
							char name, t_count *count)
{
	set_current_position(*stack);
	while (*stack != node)
	{
		if (name == 'a')
			ra(stack, count);
		else
			rb(stack, count);
		set_current_position(*stack);
	}
}

void	move_back_very_slow(t_stack_node **a, t_stack_node **b,
								t_count *count)
{
	while (*b)
	{
		init_nodes(*a, *b);
		slow_bring_to_top(a, (*b)->target_node, 'a', count);
		pa(a, b, count);
	}
}
