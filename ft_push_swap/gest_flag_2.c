/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gest_flag_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tusandri <tusandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 01:03:53 by tusandri          #+#    #+#             */
/*   Updated: 2026/04/15 01:34:01 by tusandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

static bool	is_valid_sort_flag(char *flag)
{
	if (!flag)
		return (true);
	if (ft_strcmp(flag, "--simple") == 0)
		return (true);
	if (ft_strcmp(flag, "--medium") == 0)
		return (true);
	if (ft_strcmp(flag, "--complex") == 0)
		return (true);
	if (ft_strcmp(flag, "--adaptive") == 0)
		return (true);
	return (false);
}

static int	find_first_non_flag(int argc, char **argv)
{
	int	k;
	int	start;

	start = -1;
	k = 1;
	while (k < argc)
	{
		if (ft_strncmp(argv[k], "--", 2) != 0)
		{
			if (start == -1)
				start = k;
		}
		k++;
	}
	return (start);
}

static bool	handle_single_arg(char *arg, t_args *args, char **flag)
{
	char	**split_args;

	if (!arg || !arg[0])
		return (ft_fprintf(2, "Error\n"), true);
	split_args = ft_split(arg, ' ');
	if (!split_args)
		return (true);
	args->values = extract_values(split_args, flag, &args->bench);
	if (!args->values)
		return (ft_fprintf(2, "Error\n"), free(split_args), true);
	if (*flag && !args->flag)
	{
		if (!is_valid_sort_flag(*flag))
			return (ft_fprintf(2, "Error\n"), free(split_args), true);
		args->flag = *flag;
	}
	args->free_values = true;
	free(split_args);
	return (false);
}

static int	count_non_flag_args(int argc, char **argv)
{
	int	k;
	int	count;

	k = 1;
	count = 0;
	while (k < argc)
	{
		if (ft_strncmp(argv[k], "--", 2) != 0)
			count++;
		k++;
	}
	return (count);
}

bool	check_flags(int argc, char **argv, t_args *args)
{
	int		non_flag_count;
	int		start;
	char	*flag;

	if (argc < 2)
		return (ft_fprintf(2, "Error\n"), true);
	if (repeat_flag(argv))
		return (ft_fprintf(2, "Error\n"), true);
	args->flag = get_sort_flag(argc, argv);
	if (!is_valid_sort_flag(args->flag))
		return (ft_fprintf(2, "Error\n"), true);
	args->bench = has_bench_flag(argc, argv);
	args->values = NULL;
	args->free_values = false;
	non_flag_count = count_non_flag_args(argc, argv);
	if (non_flag_count == 0)
		return (ft_fprintf(2, "Error\n"), true);
	start = find_first_non_flag(argc, argv);
	if (non_flag_count == 1)
		return (handle_single_arg(argv[start], args, &flag));
	args->values = argv + start;
	args->free_values = false;
	return (false);
}
