/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putfloat.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrandri2 <hrandri2@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 20:25:00 by hrandri2          #+#    #+#             */
/*   Updated: 2026/03/10 20:44:16 by hrandri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putfloat(double nbr, int precision)
{
	long	integer_part;
	double	fractional_part;
	int		i;
	int		count;

	count = 0;
	if (nbr < 0)
	{
		count += write(1, "-", 1);
		nbr = -nbr;
	}
	integer_part = (long)nbr;
	fractional_part = nbr - integer_part;
	count += ft_putunbr(integer_part);
	count += write(1, ".", 1);
	i = 0;
	while (i < precision)
	{
		fractional_part *= 10;
		count += ft_putchar((int)fractional_part + '0');
		fractional_part -= (int)fractional_part;
		i++;
	}
	return (count);
}