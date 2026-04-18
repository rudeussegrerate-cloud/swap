/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gest_flag_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tusandri <tusandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 01:03:53 by tusandri          #+#    #+#             */
/*   Updated: 2026/04/18 17:16:02 by tusandri         ###   ########.fr       */
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
	{
		free(*flag);
		*flag = NULL;
		return (ft_fprintf(2, "Error\n"), free_matrix(split_args), true);
	}
	if (*flag)
	{
		if (args->flag)
		{
			free(*flag);
			*flag = NULL;
			return (ft_fprintf(2, "Error\n"), free_matrix(split_args), true);
		}
		if (!is_valid_sort_flag(*flag))
		{
			free(*flag);
			*flag = NULL;
			return (ft_fprintf(2, "Error\n"), free_matrix(split_args), true);
		}
		args->flag = *flag;
		args->free_flag = true;
	}
	args->free_values = true;
	return (free_matrix(split_args), false);
}

static char	*build_combined_arg(int argc, char **argv)
{
	char	*combined_arg;
	char	*temp;
	int		i;

	combined_arg = ft_strdup(argv[1]);
	if (!combined_arg)
		return (NULL);
	i = 2;
	while (i < argc)
	{
		temp = ft_strjoin(combined_arg, " ");
		if (!temp)
			return (free(combined_arg), NULL);
		free(combined_arg);
		combined_arg = ft_strjoin(temp, argv[i]);
		free(temp);
		if (!combined_arg)
			return (NULL);
		i++;
	}
	return (combined_arg);
}

bool	check_flags(int argc, char **argv, t_args *args)
{
	char	*combined_arg;
	char	*flag;

	if (argc < 2)
		return (ft_fprintf(2, "Error\n"), true);
	flag = NULL;
	*args = (t_args){NULL, NULL, false, false, false};
	if (argc == 2)
		return (handle_single_arg(argv[1], args, &flag));
	combined_arg = build_combined_arg(argc, argv);
	if (!combined_arg)
		return (true);
	if (handle_single_arg(combined_arg, args, &flag))
	{
		free(combined_arg);
		free(flag);
		return (true);
	}
	free(combined_arg);
	return (false);
}
