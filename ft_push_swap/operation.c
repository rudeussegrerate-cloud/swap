/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrandri2 <hrandri2@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 15:03:35 by hrandri2          #+#    #+#             */
/*   Updated: 2026/04/14 00:20:01 by hrandri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

static int	total_operations(t_count *count)
{
	return (count->sa + count->sb + count->ss
		+ count->pa + count->pb
		+ count->ra + count->rb + count->rr
		+ count->rra + count->rrb + count->rrr);
}

void	print_count(t_count *count)
{
	ft_fprintf(2, "[bench] total_ops: %d\n", total_operations(count));
	ft_fprintf(2, "[bench] sa: %d sb: %d ss: %d pa: %d pb: %d\n", count->sa,
		count->sb, count->ss, count->pa, count->pb);
	ft_fprintf(2, "[bench] ra: %d rb: %d rr: %d rra: %d rrb: %d rrr: %d\n",
		count->ra, count->rb, count->rr, count->rra, count->rrb, count->rrr);
}
