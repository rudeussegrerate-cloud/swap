/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrandri2 <hrandri2@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 08:39:59 by hrandri2          #+#    #+#             */
/*   Updated: 2026/03/10 20:55:41 by hrandri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int check_float(const char *format, int *i, va_list args)
{
	char	data_spec;
	int		precision;

	data_spec = format[*i];
	precision = 6;
	if (data_spec == 'f')
	{
		int j = *i - 1;
		while (j >= 0 && format[j] != '%')
		{
			if (format[j] == '.')
			{
				precision = 0;
				j++;
				while (j < *i && format[j] >= '0' && format[j] <= '9')
				{
					precision = precision * 10 + (format[j] - '0');
					j++;
				}
				break;
			}
			j--;
		}
	}
	return (ft_putfloat(va_arg(args, double), precision));
}

static int	ft_check_format(const char *format, int *i, va_list args)
{
	char	data_spec;

	data_spec = format[*i];
	if (data_spec == 'f')
		return (check_float(format, i, args));
	else if (data_spec == 'c')
		return (ft_putchar(va_arg(args, int)));
	else if (data_spec == 's')
		return (ft_putstr(va_arg(args, char *)));
	else if (data_spec == 'u')
		return (ft_putunbr(va_arg(args, unsigned int)));
	else if (data_spec == 'i' || data_spec == 'd')
		return (ft_putnbr(va_arg(args, int)));
	else if (data_spec == 'X')
		return (ft_hexa_maj(va_arg(args, unsigned int)));
	else if (data_spec == 'x')
		return (ft_hexa_min(va_arg(args, unsigned int)));
	else if (data_spec == 'p')
		return (ft_hexa_pointer(va_arg(args, int *)));
	else if (data_spec == '%')
		return (ft_putchar('%'));
	return (-1);
}

static int	ft_handle_char(const char *format, int *i, va_list args)
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
		return (ft_check_format(format, i, args));
	}
	ret = write(1, &format[*i], 1);
	if (ret == -1)
		return (-1);
	return (1);
}

int	ft_printf(const char *format, ...)
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
		result = ft_handle_char(format, &i, args);
		if (result == -1)
			return (-1);
		len += result;
		i++;
	}
	va_end(args);
	return (len);
}

