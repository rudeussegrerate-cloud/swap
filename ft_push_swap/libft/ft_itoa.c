/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrandri2 <hrandri2@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 21:51:13 by hrandri2          #+#    #+#             */
/*   Updated: 2026/02/04 19:51:01 by hrandri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_intlen(long n)
{
	int	len;

	len = 0;
	if (n == 0)
		len = 1;
	while (n > 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

static int	ft_isneg(int n)
{
	if (n < 0)
		return (1);
	return (0);
}

static char	*ft_str(char *str, int len, int neg, long num)
{
	int	i;

	str[len + neg] = '\0';
	i = len + neg - 1;
	while (num > 0)
	{
		str[i--] = (num % 10) + '0';
		num = num / 10;
	}
	if (len == 1 && i == 0)
		str[i] = '0';
	if (neg == 1)
		str[0] = '-';
	return (str);
}

char	*ft_itoa(int n)
{
	char		*str;
	int			len;
	int			neg;
	long		num;

	neg = ft_isneg(n);
	num = (long)n;
	if (neg == 1)
		num = -num;
	len = ft_intlen(num);
	str = malloc(sizeof(char) * (len + neg + 1));
	if (!str)
		return (NULL);
	str = ft_str(str, len, neg, num);
	return (str);
}
