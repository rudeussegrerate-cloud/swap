#include "push_swap.h"

/* sa: swap the first 2 elements of stack a */
void	sa(t_stack **a)
{
	t_stack	*tmp;

	if (!*a || !(*a)->next)
		return ;
	tmp = (*a)->next;
	(*a)->next = tmp->next;
	tmp->next = *a;
	*a = tmp;
	ft_putstr_fd("sa\n", 1);
}

/* sb: swap the first 2 elements of stack b */
void	sb(t_stack **b)
{
	t_stack	*tmp;

	if (!*b || !(*b)->next)
		return ;
	tmp = (*b)->next;
	(*b)->next = tmp->next;
	tmp->next = *b;
	*b = tmp;
	ft_putstr_fd("sb\n", 1);
}

/* ss: sa and sb at the same time */
void	ss(t_stack **a, t_stack **b)
{
	t_stack	*tmp;

	if (*a && (*a)->next)
	{
		tmp = (*a)->next;
		(*a)->next = tmp->next;
		tmp->next = *a;
		*a = tmp;
	}
	if (*b && (*b)->next)
	{
		tmp = (*b)->next;
		(*b)->next = tmp->next;
		tmp->next = *b;
		*b = tmp;
	}
	ft_putstr_fd("ss\n", 1);
}

/* pa: push top of b onto a */
void	pa(t_stack **a, t_stack **b)
{
	t_stack	*node;

	if (!*b)
		return ;
	node = *b;
	*b = (*b)->next;
	node->next = *a;
	*a = node;
	ft_putstr_fd("pa\n", 1);
}

/* pb: push top of a onto b */
void	pb(t_stack **a, t_stack **b)
{
	t_stack	*node;

	if (!*a)
		return ;
	node = *a;
	*a = (*a)->next;
	node->next = *b;
	*b = node;
	ft_putstr_fd("pb\n", 1);
}

/* ra: rotate a — top element goes to the bottom */
void	ra(t_stack **a)
{
	t_stack	*last;

	if (!*a || !(*a)->next)
		return ;
	last = *a;
	while (last->next)
		last = last->next;
	last->next = *a;
	*a = (*a)->next;
	last->next->next = NULL;
	ft_putstr_fd("ra\n", 1);
}

/* rb: rotate b — top element goes to the bottom */
void	rb(t_stack **b)
{
	t_stack	*last;

	if (!*b || !(*b)->next)
		return ;
	last = *b;
	while (last->next)
		last = last->next;
	last->next = *b;
	*b = (*b)->next;
	last->next->next = NULL;
	ft_putstr_fd("rb\n", 1);
}

/* rr: ra and rb at the same time */
void	rr(t_stack **a, t_stack **b)
{
	t_stack	*last;

	if (*a && (*a)->next)
	{
		last = *a;
		while (last->next)
			last = last->next;
		last->next = *a;
		*a = (*a)->next;
		last->next->next = NULL;
	}
	if (*b && (*b)->next)
	{
		last = *b;
		while (last->next)
			last = last->next;
		last->next = *b;
		*b = (*b)->next;
		last->next->next = NULL;
	}
	ft_putstr_fd("rr\n", 1);
}

/* rra: reverse rotate a — bottom element goes to the top */
void	rra(t_stack **a)
{
	t_stack	*curr;
	t_stack	*prev;

	if (!*a || !(*a)->next)
		return ;
	curr = *a;
	prev = NULL;
	while (curr->next)
	{
		prev = curr;
		curr = curr->next;
	}
	curr->next = *a;
	*a = curr;
	prev->next = NULL;
	ft_putstr_fd("rra\n", 1);
}

/* rrb: reverse rotate b — bottom element goes to the top */
void	rrb(t_stack **b)
{
	t_stack	*curr;
	t_stack	*prev;

	if (!*b || !(*b)->next)
		return ;
	curr = *b;
	prev = NULL;
	while (curr->next)
	{
		prev = curr;
		curr = curr->next;
	}
	curr->next = *b;
	*b = curr;
	prev->next = NULL;
	ft_putstr_fd("rrb\n", 1);
}

/* rrr: rra and rrb at the same time */
void	rrr(t_stack **a, t_stack **b)
{
	t_stack	*curr;
	t_stack	*prev;

	if (*a && (*a)->next)
	{
		curr = *a;
		prev = NULL;
		while (curr->next)
		{
			prev = curr;
			curr = curr->next;
		}
		curr->next = *a;
		*a = curr;
		prev->next = NULL;
	}
	if (*b && (*b)->next)
	{
		curr = *b;
		prev = NULL;
		while (curr->next)
		{
			prev = curr;
			curr = curr->next;
		}
		curr->next = *b;
		*b = curr;
		prev->next = NULL;
	}
	ft_putstr_fd("rrr\n", 1);
}
