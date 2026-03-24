/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexa_pointer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrandri2 <hrandri2@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 08:27:28 by hrandri2          #+#    #+#             */
/*   Updated: 2026/03/21 10:04:37 by hrandri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_hexa_pointer(void *nbr)
{
	const char		*hex_chars;
	char			hex[16];
	uintptr_t	addr;
	int				i;
	int				count;

	if (nbr == NULL)
	{
		write(1, "(nil)", 5);
		return (5);
	}
	i = 15;
	count = 0;
	hex_chars = "0123456789abcdef";
	addr = (uintptr_t)nbr;
	while (addr != 0)
	{
		hex[i] = hex_chars[addr % 16];
		addr = addr / 16;
		i--;
	}
	count += write(1, "0x", 2);
	count += write(1, &hex[i + 1], 16 - i - 1);
	return (count);
}
