/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex_sort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrandri2 <hrandri2@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 19:57:59 by hrandri2          #+#    #+#             */
/*   Updated: 2026/03/23 22:50:41 by hrandri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

static void assign_final_index(t_stack_node *stack)
{
    t_stack_node *curr;
    t_stack_node *cmp;

    curr = stack;
    while (curr)
    {
        cmp = stack;
        curr->final_index = 0;
        while (cmp)
        {
            if (cmp->value < curr->value)
                curr->final_index++;
            cmp = cmp->next;
        }
        curr = curr->next;
    }
}

static int get_max_bits(t_stack_node *stack)
{
    t_stack_node *head;
    int max;
    int max_bits;

    head = stack;
    max = 0;
    while (head)
    {
        if (head->final_index > max)
            max = head->final_index;
        head = head->next;
    }
    max_bits = 0;
    while ((max >> max_bits) != 0)
        max_bits++;
    return (max_bits);
}

static int	find_bit_zero_pos(t_stack_node *a, int bit)
{
	int		pos;

	pos = 0;
	while (a)
	{
		if (((a->final_index >> bit) & 1) == 0)
			return (pos);
		a = a->next;
		pos++;
	}
	return (-1);
}

static int	count_bit_zero(t_stack_node *a, int bit)
{
	int	count;

	count = 0;
	while (a)
	{
		if (((a->final_index >> bit) & 1) == 0)
			count++;
		a = a->next;
	}
	return (count);
}

void	radix_sort(t_stack_node **stack_a, t_stack_node **stack_b, t_count *count)
{
	int		i;
	int		max_bits;
	int		zeros;
	int		pos;
	int		len;

	if (*stack_a == NULL)
		return ;
	assign_final_index(*stack_a);
	max_bits = get_max_bits(*stack_a);
	i = 0;
	while (i < max_bits)
	{
		zeros = count_bit_zero(*stack_a, i);
		if (!zeros)
		{
			i++;
			continue ;
		}
		while (zeros-- > 0)
		{
			pos = find_bit_zero_pos(*stack_a, i);
			len = stack_len(*stack_a);
			if (pos <= len / 2)
				while (pos-- > 0)
					ra(stack_a, count);
			else
				while (len - pos-- > 0)
					rra(stack_a, count);
			pb(stack_b, stack_a, count);
		}
		while (*stack_b)
			pa(stack_a, stack_b, count);
		i++;
	}
}
