/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tusandri <tusandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 08:39:10 by hrandri2          #+#    #+#             */
/*   Updated: 2026/03/30 22:02:18 by tusandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

static void	swap(t_stack_node **head)
{
	int	len;

	len = stack_len(*head);
	if (NULL == *head || NULL == head || 1 == len)
		return ;
	*head = (*head)->next;
	(*head)->prev->prev = *head;
	(*head)->prev->next = (*head)->next;
	if ((*head)->next)
		(*head)->next->prev = (*head)->prev;
	(*head)->next = (*head)->prev;
	(*head)->prev = NULL;
}

void	sa(t_stack_node	**a, t_count *count)
{
	swap(a);
	write(1, "sa\n", 3);
	count->sa++;
}

void	sb(t_stack_node **b, t_count *count)
{
	swap(b);
	write(1, "sb\n", 3);
	count->sb++;
}

void	ss(t_stack_node **a, t_stack_node **b, t_count *count)
{
	swap(a);
	swap(b);
	write(1, "ss\n", 3);
	count->ss++;
}
