/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_find_cost.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrandri2 <hrandri2@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 01:47:03 by hrandri2          #+#    #+#             */
/*   Updated: 2026/04/08 01:56:08 by hrandri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

t_stack_node	*find_insert_position(t_stack_node *a, int value)
{
	t_stack_node	*current;
	t_stack_node	*smallest;
	t_stack_node	*best;
	int				best_diff;

	smallest = find_smallest(a);
	best = smallest;
	best_diff = INT_MAX;
	current = a;
	while (current)
	{
		if (current->value > value && current->value - value < best_diff)
		{
			best_diff = current->value - value;
			best = current;
		}
		current = current->next;
	}
	return (best);
}

int	cost_to_top(t_stack_node *stack, t_stack_node *node)
{
	int	len;
	int	pos;

	len = stack_len(stack);
	pos = node->current_position;
	if (node->above_median)
		return (pos);
	else
		return (len - pos);
}

int	calculate_total_cost(t_stack_node *a, t_stack_node *b,
								t_stack_node *node)
{
	t_stack_node	*target;
	int				cost_a;
	int				cost_b;

	target = find_insert_position(a, node->value);
	cost_a = cost_to_top(a, target);
	cost_b = cost_to_top(b, node);
	return (cost_a + cost_b);
}

t_stack_node	*find_cheapest_limited(t_stack_node *a, t_stack_node *b,
										int percent)
{
	t_stack_node	*pos_tab[2];
	int				tab[3];
	int				i;

	set_current_position(a);
	set_current_position(b);
	tab[0] = (stack_len(b) * percent) / 100;
	if (tab[0] < 1)
		tab[0] = 1;
	pos_tab[0] = b;
	pos_tab[1] = b;
	tab[1] = INT_MAX;
	i = 0;
	while (pos_tab[0] && i < tab[0])
	{
		tab[2] = calculate_total_cost(a, b, pos_tab[0]);
		if (tab[2] < tab[1])
		{
			tab[1] = tab[2];
			pos_tab[1] = pos_tab[0];
		}
		pos_tab[0] = pos_tab[0]->next;
		i++;
	}
	return (pos_tab[1]);
}
