/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex_sort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tusandri <tusandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 23:10:16 by hrandri2          #+#    #+#             */
/*   Updated: 2026/04/18 15:56:51 by tusandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

void	bring_to_top(t_stack_node **a, t_stack_node *node, t_count *count)
{
	int	pos;
	int	len;

	pos = 0;
	len = stack_len(*a);
	set_current_position(*a);
	pos = node->current_position;
	if (pos <= len / 2)
	{
		while (*a != node)
			ra(a, count);
	}
	else
	{
		while (*a != node)
			rra(a, count);
	}
}

static int	get_max_bits(t_stack_node *a)
{
	int				max_index;
	int				digits;
	int				temp;
	t_stack_node	*current;

	max_index = 0;
	current = a;
	while (current)
	{
		if (current->final_index > max_index)
			max_index = current->final_index;
		current = current->next;
	}
	if (max_index == 0)
		return (1);
	digits = 0;
	temp = max_index;
	while (temp > 0)
	{
		temp /= 10;
		digits++;
	}
	return (digits);
}

static void	sort_by_bit(t_stack_node **a, t_stack_node **b,
								t_count *count, int exp)
{
	int	len;
	int	i;
	int	d;
	int	pushed;

	pushed = 0;
	d = 0;
	while (d <= 9)
	{
		len = stack_len(*a);
		i = 0;
		while (i < len)
		{
			if (((*a)->final_index / exp) % 10 == d)
				(pb(b, a, count), pushed++);
			else
				ra(a, count);
			i++;
		}
		d++;
	}
	while (pushed > 0)
		(pa(a, b, count), pushed--);
}

static void	count_len_stack(t_stack_node **a, t_stack_node **b, int len,
								t_count *count)
{
	if (len <= 1)
		return ;
	assign_final_index(*a);
	if (len == 2)
	{
		if ((*a)->value > (*a)->next->value)
			sa(a, count);
		return ;
	}
	if (len == 3)
	{
		sort_small_a(a, count, len);
		return ;
	}
	if (len == 5)
	{
		sort_five(a, b, count);
		return ;
	}
}

void	radix_sort(t_stack_node **a, t_stack_node **b, t_count *count)
{
	int	len;
	int	max_digits;
	int	digit;
	int	exp;

	if (!a || !*a)
		return ;
	len = stack_len(*a);
	count_len_stack(a, b, len, count);
	max_digits = get_max_bits(*a);
	digit = 0;
	exp = 1;
	while (digit < max_digits)
	{
		sort_by_bit(a, b, count, exp);
		exp *= 10;
		digit++;
	}
}
