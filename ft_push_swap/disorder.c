/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disorder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tusandri <tusandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 21:48:10 by hrandri2          #+#    #+#             */
/*   Updated: 2026/03/30 22:02:52 by tusandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

float	compute_disorder(t_stack_node *a)
{
	int				mistake;
	int				total_pair;
	t_stack_node	*current;
	t_stack_node	*runner;

	mistake = 0;
	total_pair = 0;
	current = a;
	while (current)
	{
		runner = current->next;
		while (runner)
		{
			total_pair++;
			if (current->value > runner->value)
				mistake++;
			runner = runner->next;
		}
		current = current->next;
	}
	if (total_pair == 0)
		return (0.0);
	return ((float)mistake / (float)total_pair);
}
