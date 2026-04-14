/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tusandri <tusandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 18:34:37 by hrandri2          #+#    #+#             */
/*   Updated: 2026/03/30 22:02:25 by tusandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FPRINTF_H
# define FT_FPRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>

int				ft_fputchar(int fd, char c);
int				ft_fputstr(int fd, char *str);
int				ft_fputnbr(int fd, int nbr);
int				ft_count_len(long n);
int				ft_fputfloat(int fd, double nbr, int precision);
int				ft_fprintf(int fd, const char *format, ...);

#endif
