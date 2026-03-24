/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrandri2 <hrandri2@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 08:36:05 by hrandri2          #+#    #+#             */
/*   Updated: 2026/03/23 23:03:16 by hrandri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

static void	adaptive_flag(int disorder_percent, t_stack_node *a,
				t_stack_node *b, t_count *count)
{
	if (disorder_percent < 20)
		push_swap(&a, &b, count);
	else if (disorder_percent >= 20 && disorder_percent < 50)
		medium_sort(&a, &b, count);
	else
		radix_sort(&a, &b, count);
}

static void	is_flag(char *arg, t_stack_node *a, t_stack_node *b,
				int disorder_percent, t_count *count)
{
	if (!arg)
		return ;
	if (ft_strcmp(arg, "--simple") == 0)
		push_swap(&a, &b, count);
	else if (ft_strcmp(arg, "--medium") == 0)
		medium_sort(&a, &b, count);
	else if (ft_strcmp(arg, "--complex") == 0)
		radix_sort(&a, &b, count);
	else if (ft_strcmp(arg, "--adaptive") == 0)
		adaptive_flag(disorder_percent, a, b, count);
	else
		write(1, "Error\n", 6);
}

static void	check_flags(int argc, char **argv, t_args *args)
{
	args->flag = NULL;
	args->values = NULL;
	args->free_values = false;
	if (ft_strncmp(argv[2], "--", 2) == 0)
	{
		args->flag = argv[2];
		if (argc == 3)
			return ;
		if (argc == 4)
		{
			args->values = ft_split(argv[3], ' ');
			args->free_values = true;
			return ;
		}
		args->values = argv + 3;
		return ;
	}
	if (argc == 3)
	{
		args->values = ft_split(argv[2], ' ');
		args->free_values = true;
		return ;
	}
	args->values = argv + 2;
}

static double	run_sort(t_stack_node *a, t_stack_node *b, char *flag, t_count *count)
{
	double	disorder;
	int		disorder_percent;

	disorder = compute_disorder(a);
	disorder_percent = disorder * 100;
	if (stack_sorted(a))
		return (0);
	if (stack_len(a) == 2)
		sa(&a, count);
	else if (stack_len(a) == 3)
		tiny_sort(&a, count);
	else if (flag)
		is_flag(flag, a, b, disorder_percent, count);
	else
		adaptive_flag(disorder_percent, a, b, count);
	return  (disorder);
}

int	main(int argc, char **argv)
{
	t_stack_node	*a;
	t_stack_node	*b;
	t_args			args;
	t_count		count;

	if (argc < 2)
		return (1);
	check_flags(argc, argv, &args);
	a = NULL;
	b = NULL;
	count = (t_count){0};
	stack_init(&a, args.values, args.free_values);
	double disorder = run_sort(a, b, args.flag, &count);

	if (ft_strcmp(argv[1], "--bench") == 0)
		bench_mode(disorder, argv[2], &count);

	free_stack(&a);
	return (0);
}
