/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrandri2 <hrandri2@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 08:36:31 by hrandri2          #+#    #+#             */
/*   Updated: 2026/03/22 07:21:58 by hrandri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "ft_push_swap.h"

static void	rotate_both(t_stack_node **a,
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

static void	reverse_rotate_both(t_stack_node **a,
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

static void	move_nodes(t_stack_node **a, t_stack_node **b, t_count *count)
{
	t_stack_node	*cheapest_node;

	cheapest_node = return_cheapest(*b);
	if (cheapest_node->above_median
		&& cheapest_node->target_node->above_median)
		rotate_both(a, b, cheapest_node, count);
	else if (!(cheapest_node->above_median)
		&& !(cheapest_node->target_node->above_median))
		reverse_rotate_both(a, b, cheapest_node, count);
	finish_rotation(b, cheapest_node, 'b', count);
	finish_rotation(a, cheapest_node->target_node, 'a', count);
	pa(a, b, count);
}

void	push_swap(t_stack_node **a, t_stack_node **b, t_count *count)
{
	t_stack_node	*smallest;
	int				len_a;

	len_a = stack_len(*a);
	while (len_a-- > 3)
		pb(b, a, count);
	tiny_sort(a, count);
	while (*b)
	{
		init_nodes(*a, *b);
		move_nodes(a, b, count);
	}
	set_current_position(*a);
	smallest = find_smallest(*a);
	if (smallest->above_median)
	{
		while (*a != smallest)
			ra(a, count);
	}
	else
	{
		while (*a != smallest)
			rra(a, count);
	}
}
