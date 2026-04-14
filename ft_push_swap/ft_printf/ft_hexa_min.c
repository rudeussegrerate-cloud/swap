/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexa_min.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tusandri <tusandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 22:52:07 by hrandri2          #+#    #+#             */
/*   Updated: 2026/03/30 22:02:40 by tusandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_hexa_min(unsigned int nbr)
{
	char	*base;
	int		len;

	len = 0;
	base = "0123456789abcdef";
	if ((nbr / 16) != 0)
		len = ft_hexa_min((nbr / 16));
	len += write(1, &base[(nbr % 16)], 1);
	return (len);
}
