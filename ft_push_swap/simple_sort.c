/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrandri2 <hrandri2@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 08:36:31 by hrandri2          #+#    #+#             */
/*   Updated: 2026/04/14 00:21:57 by hrandri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

static void	final_rotation(t_stack_node **a, int original_len, t_count *count)
{
	t_stack_node	*smallest;

	set_current_position(*a);
	smallest = find_smallest(*a);
	if (original_len <= 50)
	{
		while (*a != smallest)
			ra(a, count);
	}
	else
	{
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
}

void	push_swap(t_stack_node **a, t_stack_node **b, t_count *count)
{
	int	len;
	int	original_len;
	int	percent;

	len = stack_len(*a);
	original_len = len;
	if (original_len <= 100)
		percent = 2;
	else
		percent = 15;
	while (len-- > 3)
		pb(b, a, count);
	tiny_sort(a, count);
	if (original_len <= 50)
	{
		while (*b)
			move_slow(a, b, count);
	}
	else
	{
		while (*b)
			move_fast(a, b, count, percent);
	}
	final_rotation(a, original_len, count);
}
