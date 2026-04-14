/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fputnbr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tusandri <tusandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 23:04:55 by hrandri2          #+#    #+#             */
/*   Updated: 2026/03/30 22:02:29 by tusandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fprintf.h"

int	ft_fputnbr(int fd, int nbr)
{
	long	nb;
	long	digit;

	nb = nbr;
	digit = 0;
	if (nb < 0)
	{
		write(1, "-", 1);
		nb = -nb;
	}
	if (nb / 10 != 0)
		ft_fputnbr(fd, nb / 10);
	digit = (nb % 10) + '0';
	ft_fputchar(fd, digit);
	return (ft_count_len(nbr));
}
