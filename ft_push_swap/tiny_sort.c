/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tiny_sort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrandri2 <hrandri2@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 08:39:31 by hrandri2          #+#    #+#             */
/*   Updated: 2026/04/11 00:32:46 by hrandri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

bool	stack_sorted(t_stack_node *stack)
{
	if (NULL == stack)
		return (1);
	while (stack->next)
	{
		if (stack->value > stack->next->value)
			return (false);
		stack = stack->next;
	}
	return (true);
}

static t_stack_node	*find_highest(t_stack_node *stack)
{
	int				highest;
	t_stack_node	*highest_node;

	if (NULL == stack)
		return (NULL);
	highest = INT_MIN;
	while (stack)
	{
		if (stack->value > highest)
		{
			highest = stack->value;
			highest_node = stack;
		}
		stack = stack->next;
	}
	return (highest_node);
}

void	tiny_sort(t_stack_node **a, t_count *count)
{
	t_stack_node	*highest_node;

	highest_node = find_highest(*a);
	if (*a == highest_node)
		ra(a, count);
	else if ((*a)->next == highest_node)
		rra(a, count);
	if ((*a)->value > (*a)->next->value)
		sa(a, count);
}

void	sort_small_a(t_stack_node **a, t_count *c, int len)
{
	if (len == 2 && (*a)->final_index > (*a)->next->final_index)
		sa(a, c);
	else if (len == 3)
		tiny_sort(a, c);
}

void	sort_five(t_stack_node **a, t_stack_node **b, t_count *count)
{
	t_stack_node	*smallest;

	smallest = find_smallest(*a);
	bring_to_top(a, smallest, count);
	pb(b, a, count);
	smallest = find_smallest(*a);
	bring_to_top(a, smallest, count);
	pb(b, a, count);
	tiny_sort(a, count);
	pa(a, b, count);
	pa(a, b, count);
}
