/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrandri2 <hrandri2@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 08:38:31 by hrandri2          #+#    #+#             */
/*   Updated: 2026/03/22 06:28:45 by hrandri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

static void	rotate(t_stack_node **stack)
{
	t_stack_node	*last_node;
	int				len;

	len = stack_len(*stack);
	if (NULL == stack || NULL == *stack || 1 == len)
		return ;
	last_node = find_last_node(*stack);
	last_node->next = *stack;
	*stack = (*stack)->next;
	(*stack)->prev = NULL;
	last_node->next->prev = last_node;
	last_node->next->next = NULL;
}	

void	ra(t_stack_node **a, t_count *count)
{
	rotate(a);
	write(1, "ra\n", 3);
	count->ra++;
}

void	rb(t_stack_node **b, t_count *count)
{
	rotate(b);
	write(1, "rb\n", 3);
	count->rb++;
}

void	rr(t_stack_node **a, t_stack_node **b, t_count *count)
{
	rotate(a);
	rotate(b);
	write(1, "rr\n", 3);
	count->rr++;
}
