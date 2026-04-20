#include "push_swap.h"

/* ------------------------------------------------------------------ */
/* Small-sort helpers                                                  */
/* ------------------------------------------------------------------ */

static void	sort_two(t_stack **a)
{
	if ((*a)->index > (*a)->next->index)
		sa(a);
}

/*
** Sort exactly 3 elements optimally (≤2 ops).
** Works for any three distinct index values.
*/
static void	sort_three(t_stack **a)
{
	int	top;
	int	mid;
	int	bot;

	top = (*a)->index;
	mid = (*a)->next->index;
	bot = (*a)->next->next->index;
	if (top < mid && mid < bot)
		return ;
	if (top < bot && bot < mid)
	{
		rra(a);
		sa(a);
	}
	else if (mid < top && top < bot)
		sa(a);
	else if (bot < top && top < mid)
		rra(a);
	else if (mid < bot && bot < top)
		ra(a);
	else
	{
		sa(a);
		rra(a);
	}
}

/*
** Push (size − 3) smallest elements to b, sort remaining 3, push back.
** Works for size == 4 or 5.
*/
static void	push_by_index(t_stack **a, t_stack **b, int target)
{
	int		pos;
	int		sz;
	t_stack	*curr;

	pos = 0;
	sz = stack_size(*a);
	curr = *a;
	while (curr && curr->index != target)
	{
		pos++;
		curr = curr->next;
	}
	if (pos <= sz / 2)
		while (pos-- > 0)
			ra(a);
	else
	{
		pos = sz - pos;
		while (pos-- > 0)
			rra(a);
	}
	pb(a, b);
}

static void	sort_small(t_stack **a, t_stack **b, int size)
{
	int	i;

	i = 0;
	while (i < size - 3)
	{
		push_by_index(a, b, i);
		i++;
	}
	sort_three(a);
	while (*b)
		pa(a, b);
}

/* ------------------------------------------------------------------ */
/* Turk algorithm — helpers                                            */
/* ------------------------------------------------------------------ */

static int	ft_max(int a, int b)
{
	return (a > b ? a : b);
}

static int	ft_min(int a, int b)
{
	return (a < b ? a : b);
}

/*
** Total cost (in push_swap operations) to bring element at position
** pa in stack a to the top, AND bring position pb in stack b to the
** top, using combined rr/rrr when both rotate in the same direction.
*/
static int	combined_cost(int pa, int pb, int sa, int sb)
{
	int	ra;
	int	rra;
	int	rb;
	int	rrb;

	ra = pa;
	rra = sa - pa;
	rb = pb;
	rrb = sb - pb;
	return (ft_min(ft_min(ft_max(ra, rb), ft_max(rra, rrb)),
			ft_min(ra + rrb, rra + rb)));
}

/*
** b is maintained in circular-descending order (one ascending wrap).
** Return the position in b that must be rotated to the front so that
** pa()'s mirror pb() inserts the element with value `v` correctly.
**
** The target position is the one occupied by the element just SMALLER
** than v (or the max of b if v is a new extreme).
*/
static int	target_in_b(t_stack *b, int v)
{
	int		n;
	int		pos;
	int		best_pos;
	int		best_val;
	int		max_pos;
	int		max_val;
	t_stack	*curr;
	t_stack	*nxt;

	n = stack_size(b);
	if (n == 0)
		return (0);
	best_pos = 0;
	best_val = INT_MIN;
	max_pos = 0;
	max_val = INT_MIN;
	curr = b;
	pos = 0;
	while (curr)
	{
		if (curr->value > max_val)
		{
			max_val = curr->value;
			max_pos = pos;
		}
		nxt = curr->next ? curr->next : b;
		if (curr->value > v && nxt->value < v)
		{
			if (curr->value < best_val || best_val == INT_MIN)
			{
				best_val = curr->value;
				best_pos = (pos + 1) % n;
			}
		}
		pos++;
		curr = curr->next;
	}
	if (best_val == INT_MIN)
		return (max_pos);
	return (best_pos);
}

/*
** a is maintained in circular-ascending order.
** Return the position in a of the element that must be at the front
** so that pa(v) inserts v in the correct sorted slot.
**
** The target is the smallest element in a that is strictly > v, or
** the position of the minimum if v > max(a).
*/
static int	target_in_a(t_stack *a, int v)
{
	int		pos;
	int		best_pos;
	int		best_val;
	int		min_pos;
	int		min_val;
	t_stack	*curr;

	best_pos = 0;
	best_val = INT_MAX;
	min_pos = 0;
	min_val = INT_MAX;
	curr = a;
	pos = 0;
	while (curr)
	{
		if (curr->value < min_val)
		{
			min_val = curr->value;
			min_pos = pos;
		}
		if (curr->value > v && curr->value < best_val)
		{
			best_val = curr->value;
			best_pos = pos;
		}
		pos++;
		curr = curr->next;
	}
	if (best_val == INT_MAX)
		return (min_pos);
	return (best_pos);
}

/* ------------------------------------------------------------------ */
/* Turk algorithm — rotation execution                                 */
/* ------------------------------------------------------------------ */

/*
** Rotate stack a by `cnt` positions forward (ra) or backward (rra).
** sign > 0 → ra, sign < 0 → rra.
*/
static void	rotate_a(t_stack **a, int cnt, int sign)
{
	if (sign > 0)
		while (cnt-- > 0)
			ra(a);
	else
		while (cnt-- > 0)
			rra(a);
}

static void	rotate_b(t_stack **b, int cnt, int sign)
{
	if (sign > 0)
		while (cnt-- > 0)
			rb(b);
	else
		while (cnt-- > 0)
			rrb(b);
}

/*
** Rotate a to bring position pa to the top, and b to bring position
** pb to the top.  Use rr/rrr when both rotate in the same direction.
*/
static void	do_rotations(t_stack **a, t_stack **b, int pa, int pb,
		int sz_a, int sz_b)
{
	int	ra;
	int	rra;
	int	rb;
	int	rrb;
	int	best;

	ra = pa;
	rra = sz_a - pa;
	rb = pb;
	rrb = sz_b - pb;
	best = ft_min(ft_min(ft_max(ra, rb), ft_max(rra, rrb)),
			ft_min(ra + rrb, rra + rb));
	if (best == ft_max(ra, rb))
	{
		while (ra > 0 && rb > 0)
		{
			rr(a, b);
			ra--;
			rb--;
		}
		rotate_a(a, ra, 1);
		rotate_b(b, rb, 1);
	}
	else if (best == ft_max(rra, rrb))
	{
		while (rra > 0 && rrb > 0)
		{
			rrr(a, b);
			rra--;
			rrb--;
		}
		rotate_a(a, rra, -1);
		rotate_b(b, rrb, -1);
	}
	else if (best == ra + rrb)
	{
		rotate_a(a, ra, 1);
		rotate_b(b, rrb, -1);
	}
	else
	{
		rotate_a(a, rra, -1);
		rotate_b(b, rb, 1);
	}
}

/* ------------------------------------------------------------------ */
/* Turk algorithm — phase 1: push to b                                 */
/* ------------------------------------------------------------------ */

static void	turk_push_to_b(t_stack **a, t_stack **b)
{
	int		sz_a;
	int		sz_b;
	int		best_pa;
	int		best_tb;
	int		best_cost;
	int		pos;
	int		tb;
	int		cost;
	t_stack	*curr;

	while (stack_size(*a) > 3)
	{
		sz_a = stack_size(*a);
		sz_b = stack_size(*b);
		best_pa = 0;
		best_tb = 0;
		best_cost = INT_MAX;
		curr = *a;
		pos = 0;
		while (curr)
		{
			tb = target_in_b(*b, curr->value);
			cost = combined_cost(pos, tb, sz_a, sz_b);
			if (cost < best_cost)
			{
				best_cost = cost;
				best_pa = pos;
				best_tb = tb;
			}
			pos++;
			curr = curr->next;
		}
		do_rotations(a, b, best_pa, best_tb, sz_a, sz_b);
		pb(a, b);
	}
	sort_three(a);
}

/* ------------------------------------------------------------------ */
/* Turk algorithm — phase 2: push from b to a                          */
/* ------------------------------------------------------------------ */

static void	turk_push_to_a(t_stack **a, t_stack **b)
{
	int		sz_a;
	int		sz_b;
	int		best_pb;
	int		best_ta;
	int		best_cost;
	int		pos;
	int		ta;
	int		cost;
	t_stack	*curr;

	while (*b)
	{
		sz_a = stack_size(*a);
		sz_b = stack_size(*b);
		best_pb = 0;
		best_ta = 0;
		best_cost = INT_MAX;
		curr = *b;
		pos = 0;
		while (curr)
		{
			ta = target_in_a(*a, curr->value);
			cost = combined_cost(ta, pos, sz_a, sz_b);
			if (cost < best_cost)
			{
				best_cost = cost;
				best_ta = ta;
				best_pb = pos;
			}
			pos++;
			curr = curr->next;
		}
		do_rotations(a, b, best_ta, best_pb, sz_a, sz_b);
		pa(a, b);
	}
}

/* Rotate a so the minimum element is at the top. */
static void	rotate_to_min(t_stack **a)
{
	int		min_pos;
	int		min_val;
	int		sz;
	int		pos;
	t_stack	*curr;

	min_pos = 0;
	min_val = INT_MAX;
	sz = stack_size(*a);
	pos = 0;
	curr = *a;
	while (curr)
	{
		if (curr->value < min_val)
		{
			min_val = curr->value;
			min_pos = pos;
		}
		pos++;
		curr = curr->next;
	}
	if (min_pos <= sz / 2)
		while (min_pos-- > 0)
			ra(a);
	else
	{
		min_pos = sz - min_pos;
		while (min_pos-- > 0)
			rra(a);
	}
}

/* ------------------------------------------------------------------ */
/* Entry point                                                         */
/* ------------------------------------------------------------------ */

void	sort_stack(t_stack **a, t_stack **b)
{
	int	size;

	size = stack_size(*a);
	if (size <= 1)
		return ;
	assign_index(*a);
	if (size == 2)
		sort_two(a);
	else if (size == 3)
		sort_three(a);
	else if (size <= 5)
		sort_small(a, b, size);
	else
	{
		turk_push_to_b(a, b);
		turk_push_to_a(a, b);
		rotate_to_min(a);
	}
}
