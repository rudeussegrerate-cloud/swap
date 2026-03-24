#include "push_swap.h"

void	error_exit(t_stack **a)
{
	free_stack(a);
	ft_putstr_fd("Error\n", 2);
	exit(1);
}

/*
** Safe atoi: returns 1 on success, 0 on failure (overflow, bad chars).
** Handles sign, leading zeros, and INT range [INT_MIN, INT_MAX].
*/
int	ft_atoi_safe(const char *s, long *result)
{
	long	n;
	int		sign;
	int		i;

	n = 0;
	sign = 1;
	i = 0;
	if (!s || !s[0])
		return (0);
	if (s[i] == '-' || s[i] == '+')
	{
		if (s[i] == '-')
			sign = -1;
		i++;
	}
	if (!s[i])
		return (0);
	while (s[i] >= '0' && s[i] <= '9')
	{
		n = n * 10 + (s[i] - '0');
		if (n > 2147483648L)
			return (0);
		i++;
	}
	if (s[i])
		return (0);
	if (n * sign > (long)INT_MAX || n * sign < (long)INT_MIN)
		return (0);
	*result = n * sign;
	return (1);
}

static int	has_duplicate(t_stack *stack, int value)
{
	while (stack)
	{
		if (stack->value == value)
			return (1);
		stack = stack->next;
	}
	return (0);
}

static void	append_node(t_stack **head, int value)
{
	t_stack	*node;
	t_stack	*curr;

	node = new_node(value);
	if (!node)
		error_exit(head);
	if (!*head)
	{
		*head = node;
		return ;
	}
	curr = *head;
	while (curr->next)
		curr = curr->next;
	curr->next = node;
}

/*
** Parses a whitespace-separated string and appends integers to *head.
** Calls error_exit on invalid tokens, overflow, or duplicates.
*/
static void	parse_str(t_stack **head, const char *s)
{
	int		i;
	int		blen;
	long	val;
	char	buf[22];

	i = 0;
	while (s[i])
	{
		while (s[i] == ' ' || s[i] == '\t')
			i++;
		if (!s[i])
			break ;
		blen = 0;
		if (s[i] == '-' || s[i] == '+')
			buf[blen++] = s[i++];
		while (s[i] >= '0' && s[i] <= '9')
		{
			if (blen >= 20)
				error_exit(head);
			buf[blen++] = s[i++];
		}
		if (s[i] && s[i] != ' ' && s[i] != '\t')
			error_exit(head);
		buf[blen] = '\0';
		if (blen == 0 || (blen == 1 && (buf[0] == '-' || buf[0] == '+')))
			error_exit(head);
		if (!ft_atoi_safe(buf, &val))
			error_exit(head);
		if (has_duplicate(*head, (int)val))
			error_exit(head);
		append_node(head, (int)val);
	}
}

t_stack	*parse_args(int argc, char **argv)
{
	t_stack	*head;
	int		i;

	head = NULL;
	i = 1;
	while (i < argc)
	{
		parse_str(&head, argv[i]);
		i++;
	}
	if (!head)
		error_exit(&head);
	return (head);
}
