/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   medium_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrandri2 <hrandri2@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 22:00:53 by hrandri2          #+#    #+#             */
/*   Updated: 2026/04/14 00:23:23 by hrandri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

static void	final_rotation_slow(t_stack_node **a, t_count *count)
{
	t_stack_node	*target;

	set_current_position(*a);
	target = find_smallest(*a);
	while (*a != target)
		ra(a, count);
}

static void	final_rotation_fast(t_stack_node **a, t_count *count)
{
	t_stack_node	*target;

	set_current_position(*a);
	target = find_smallest(*a);
	if (target->above_median)
		while (*a != target)
			ra(a, count);
	else
		while (*a != target)
			rra(a, count);
}

static int	get_bucket_size(int len)
{
	int	size;

	if (len <= 50)
		size = (len / 3) + 2;
	else if (len <= 100)
		size = (len / 20) - 2;
	else if (len <= 500)
		size = (len / 23) + 1;
	else
		size = (len / 25) + 1;
	if (size <= 0)
		size = 1;
	return (size);
}

void	medium_sort(t_stack_node **a, t_stack_node **b, t_count *count)
{
	int	len;

	len = stack_len(*a);
	assign_final_index(*a);
	push_buckets(a, b, get_bucket_size(len), count);
	tiny_sort(a, count);
	if (len <= 50)
	{
		move_back_very_slow(a, b, count);
		final_rotation_slow(a, count);
	}
	else
	{
		move_back_fast(a, b, count);
		final_rotation_fast(a, count);
	}
}
