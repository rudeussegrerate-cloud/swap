/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrandri2 <hrandri2@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 08:38:48 by hrandri2          #+#    #+#             */
/*   Updated: 2026/04/08 01:01:37 by hrandri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

static long	ft_atol(const char *str)
{
	long	num;
	int		isneg;
	int		i;

	num = 0;
	isneg = 1;
	i = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'
			|| str[i] == '\n' || str[i] == '\r'
			|| str[i] == '\v' || str[i] == '\f'))
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{
		isneg *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = (num * 10) + (str[i] - '0');
		i++;
	}
	return (num * isneg);
}

static void	check_flags_number(t_stack_node **a, char **argv, int tab_count[2],
			bool flag)
{
	if (ft_strcmp(argv[(tab_count[0])], "--simple") == 0
		|| ft_strcmp(argv[(tab_count[0])], "--medium") == 0
		|| ft_strcmp(argv[(tab_count[0])], "--complex") == 0
		|| ft_strcmp(argv[(tab_count[0])], "--adaptive") == 0
		|| ft_strcmp(argv[(tab_count[0])], "--bench") == 0)
	{
		((tab_count[1]))++;
		if ((tab_count[1]) > 2)
			error_free(a, argv, flag);
		((tab_count[0]))++;
		if (argv[(tab_count[0])])
		{
			if (ft_strcmp(argv[(tab_count[0])], "--simple") == 0
				|| ft_strcmp(argv[(tab_count[0])], "--medium") == 0
				|| ft_strcmp(argv[(tab_count[0])], "--complex") == 0
				|| ft_strcmp(argv[(tab_count[0])], "--adaptive") == 0
				|| ft_strcmp(argv[(tab_count[0])], "--bench") == 0)
			{
				((tab_count[1]))++;
				((tab_count[0]))++;
			}
		}
	}
}

void	stack_init(t_stack_node **a, char **argv, bool flag_argc_2)
{
	long	nbr;
	int		tab_count[2];

	tab_count[0] = 0;
	tab_count[1] = 0;
	while (argv[(tab_count[0])])
	{
		check_flags_number(a, argv, tab_count, flag_argc_2);
		if (!argv[(tab_count[0])])
			return ;
		if (error_syntax(argv[(tab_count[0])]))
			error_free(a, argv, flag_argc_2);
		nbr = ft_atol(argv[(tab_count[0])]);
		if ((nbr > INT_MAX || nbr < INT_MIN) || error_repetition(*a, (int)nbr))
			error_free(a, argv, flag_argc_2);
		append_node(a, (int)nbr);
		(tab_count[0])++;
	}
}
