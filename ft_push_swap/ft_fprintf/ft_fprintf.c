/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrandri2 <hrandri2@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 08:39:59 by hrandri2          #+#    #+#             */
/*   Updated: 2026/04/02 20:39:21 by hrandri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fprintf.h"

static int	check_float(int fd, const char *format, int *i, va_list args)
{
	char	data_spec;
	int		precision;
	int		j;

	data_spec = format[*i];
	precision = 6;
	if (data_spec == 'f')
	{
		j = *i - 1;
		while (j >= 0 && format[j] != '%')
		{
			if (format[j] == '.')
			{
				precision = 0;
				j++;
				while (j < *i && format[j] >= '0' && format[j] <= '9')
					precision = precision * 10 + (format[j++] - '0');
				break ;
			}
			j--;
		}
	}
	return (ft_fputfloat(fd, va_arg(args, double), precision));
}

static int	ft_check_format(int fd, const char *format, int *i, va_list args)
{
	char	data_spec;

	data_spec = format[*i];
	if (data_spec == 'f')
		return (check_float(fd, format, i, args));
	else if (data_spec == 'c')
		return (ft_fputchar(fd, va_arg(args, int)));
	else if (data_spec == 's')
		return (ft_fputstr(fd, va_arg(args, char *)));
	else if (data_spec == 'i' || data_spec == 'd')
		return (ft_fputnbr(fd, va_arg(args, int)));
	else if (data_spec == '%')
		return (ft_fputchar(fd, '%'));
	return (-1);
}

static int	ft_handle_char(int fd, const char *format, int *i, va_list args)
{
	int	ret;

	if (format[*i] == '%')
	{
		if (format[*i + 1] == '\0')
			return (-1);
		(*i)++;
		if (format[*i] == '.')
		{
			(*i)++;
			while (format[*i] >= '0' && format[*i] <= '9')
				(*i)++;
		}
		return (ft_check_format(fd, format, i, args));
	}
	ret = write(fd, &format[*i], 1);
	if (ret == -1)
		return (-1);
	return (1);
}

int	ft_fprintf(int fd, const char *format, ...)
{
	va_list	args;
	int		i;
	int		len;
	int		result;

	if (!format)
		return (-1);
	va_start(args, format);
	i = 0;
	len = 0;
	while (format[i])
	{
		result = ft_handle_char(fd, format, &i, args);
		if (result == -1)
			return (-1);
		len += result;
		i++;
	}
	va_end(args);
	return (len);
}
