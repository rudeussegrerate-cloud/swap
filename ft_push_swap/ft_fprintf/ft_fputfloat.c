/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fputfloat.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tusandri <tusandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 20:25:00 by hrandri2          #+#    #+#             */
/*   Updated: 2026/03/30 22:02:27 by tusandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fprintf.h"

int	ft_fputfloat(int fd, double nbr, int precision)
{
	long	integer_part;
	double	fractional_part;
	int		i;
	int		count;

	count = 0;
	if (nbr < 0)
	{
		count += write(fd, "-", 1);
		nbr = -nbr;
	}
	integer_part = (long)nbr;
	fractional_part = nbr - integer_part;
	count += ft_fputnbr(fd, integer_part);
	count += write(fd, ".", 1);
	i = 0;
	while (i < precision)
	{
		fractional_part *= 10;
		count += ft_fputchar(fd, (int)fractional_part + '0');
		fractional_part -= (int)fractional_part;
		i++;
	}
	return (count);
}
