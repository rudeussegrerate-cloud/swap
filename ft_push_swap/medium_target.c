/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   medium_target.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrandri2 <hrandri2@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 01:30:14 by hrandri2          #+#    #+#             */
/*   Updated: 2026/04/08 01:35:05 by hrandri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

void	update_targets(t_stack_node *cur, int pos, t_stack_node **t, int *p)
{
	if (!t[0])
	{
		t[0] = cur;
		p[0] = pos;
	}
	t[1] = cur;
	p[1] = pos;
}

t_stack_node	*find_bucket_target(t_stack_node *a, int idx[2], bool *rra)
{
	int				pos;
	int				p[2];
	t_stack_node	*t[2];
	t_stack_node	*cur;

	pos = 0;
	t[0] = NULL;
	t[1] = NULL;
	cur = a;
	while (cur)
	{
		if (cur->final_index >= idx[0] && cur->final_index <= idx[1])
			update_targets(cur, pos, t, p);
		cur = cur->next;
		pos++;
	}
	if (!t[0])
		return (NULL);
	*rra = (p[0] > stack_len(a) - p[1]);
	if (*rra)
		return (t[1]);
	return (t[0]);
}

void	rotate_to_target(t_stack_node **a, t_stack_node *target,
				bool use_rra, t_count *count)
{
	while (*a != target)
	{
		if (use_rra)
			rra(a, count);
		else
			ra(a, count);
	}
}

void	advance_bucket(int idx[2], int *pushed, int bkt)
{
	idx[0] += bkt;
	idx[1] += bkt;
	*pushed = 0;
}

void	push_buckets(t_stack_node **a, t_stack_node **b, int bkt,
				t_count *count)
{
	int				idx[2];
	int				pushed;
	bool			use_rra;
	t_stack_node	*target;

	idx[0] = 0;
	idx[1] = bkt - 1;
	pushed = 0;
	while (stack_len(*a) > 3)
	{
		target = find_bucket_target(*a, idx, &use_rra);
		if (!target)
		{
			advance_bucket(idx, &pushed, bkt);
			continue ;
		}
		rotate_to_target(a, target, use_rra, count);
		pb(b, a, count);
		if ((*b)->final_index < idx[0] + (bkt / 2))
			rb(b, count);
		if (++pushed >= bkt)
			advance_bucket(idx, &pushed, bkt);
	}
}
