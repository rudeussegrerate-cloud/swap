/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tusandri <tusandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 08:36:05 by hrandri2          #+#    #+#             */
/*   Updated: 2026/04/15 01:30:24 by tusandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

bool	has_bench_flag(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (ft_strcmp(argv[i], "--bench") == 0)
			return (true);
		i++;
	}
	return (false);
}

static double	run_sort(t_sort_data *data)
{
	double	disorder;

	disorder = compute_disorder(*data->a);
	data->count->disorder_percent = (int)(disorder * 100);
	if (stack_sorted(*data->a))
		return (disorder);
	if (stack_len(*data->a) == 2)
		sa(data->a, data->count);
	else if (stack_len(*data->a) == 3)
		tiny_sort(data->a, data->count);
	else
		apply_sort_flag(data->flag, data->a, data->b, data->count);
	return (disorder);
}

static void	cleanup(t_stack_node **a, char **values, bool free_values)
{
	int	i;

	free_stack(a);
	if (free_values && values)
	{
		i = 0;
		while (values[i])
			free(values[i++]);
		free(values);
	}
}

int	main(int argc, char **argv)
{
	t_stack_node	*tab[2];
	t_args			args;
	t_count			count;
	t_sort_data		data;
	double			disorder;

	if (argc < 2)
		return (1);
	if (check_flags(argc, argv, &args))
		return (0);
	tab[0] = NULL;
	tab[1] = NULL;
	count = (t_count){0};
	stack_init(&tab[0], args.values, args.free_values);
	data = (t_sort_data){&tab[0], &tab[1], args.flag, &count};
	disorder = run_sort(&data);
	if (args.bench)
		bench_mode(disorder, args.flag, &count);
	cleanup(&tab[0], args.values, args.free_values);
	return (0);
}
