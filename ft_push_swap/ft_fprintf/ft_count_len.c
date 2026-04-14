/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_len.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tusandri <tusandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 08:27:28 by hrandri2          #+#    #+#             */
/*   Updated: 2026/03/30 22:02:23 by tusandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_count_len(long n)
{
	int		len;
	long	nb;

	nb = n;
	len = 0;
	if (nb == 0)
		len = 1;
	if (nb < 0)
		nb = nb * -1;
	while (nb > 0)
	{
		nb = nb / 10;
		len++;
	}
	if (n < 0)
		return (len + 1);
	return (len);
}
