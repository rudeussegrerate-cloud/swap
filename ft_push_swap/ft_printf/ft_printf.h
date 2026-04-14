/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tusandri <tusandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 18:34:37 by hrandri2          #+#    #+#             */
/*   Updated: 2026/03/30 22:02:42 by tusandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <stdint.h>

int				ft_putchar(char c);
int				ft_putstr(char *str);
int				ft_putnbr(int nbr);
int				ft_count_len(long n);
int				ft_printf(const char *format, ...);
int				ft_hexa_pointer(void *nbr);
unsigned int	ft_putunbr(unsigned int nbr);
int				ft_hexa_maj(unsigned int nbr);
int				ft_hexa_min(unsigned int nbr);
int				ft_putfloat(double nbr, int precision);

#endif
