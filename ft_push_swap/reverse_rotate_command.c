/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_rotate_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tusandri <tusandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 08:38:08 by hrandri2          #+#    #+#             */
/*   Updated: 2026/03/30 22:02:13 by tusandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

static void	reverse_rotate(t_stack_node **stack)
{
	t_stack_node	*last;
	int				len;

	len = stack_len(*stack);
	if (NULL == *stack || NULL == stack || 1 == len)
		return ;
	last = find_last_node(*stack);
	last->prev->next = NULL;
	last->next = *stack;
	last->prev = NULL;
	*stack = last;
	last->next->prev = last;
}

void	rra(t_stack_node **a, t_count *count)
{
	reverse_rotate(a);
	write(1, "rra\n", 4);
	count->rra++;
}

void	rrb(t_stack_node **b, t_count *count)
{
	reverse_rotate(b);
	write(1, "rrb\n", 4);
	count->rrb++;
}

void	rrr(t_stack_node **a, t_stack_node **b, t_count *count)
{
	reverse_rotate(a);
	reverse_rotate(b);
	write(1, "rrr\n", 4);
	count->rrr++;
}
