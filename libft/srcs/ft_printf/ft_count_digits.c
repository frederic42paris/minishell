/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_digits.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 14:01:30 by rrichard          #+#    #+#             */
/*   Updated: 2023/12/08 16:07:59 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	ft_count_digits(int n)
{
	int	count;

	count = 0;
	if (n < 0 && n != -2147483648)
	{
		count++;
		n = -n;
	}
	else if (n == -2147483648)
		return (11);
	if (n == 0)
		count++;
	while (n > 0)
	{
		count++;
		n /= 10;
	}
	return (count);
}

int	ft_count_digits_uns(unsigned int n)
{
	int	count;

	count = 0;
	if (n == 0)
		count++;
	while (n > 0)
	{
		count++;
		n /= 10;
	}
	return (count);
}

int	ft_count_digits_hex(unsigned int n)
{
	int	count;

	count = 0;
	if (n == 0)
		count++;
	while (n > 0)
	{
		count++;
		n /= 16;
	}
	return (count);
}
