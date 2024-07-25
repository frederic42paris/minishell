/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 15:50:01 by rrichard          #+#    #+#             */
/*   Updated: 2023/12/08 16:07:26 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	ft_putnbr_uns(unsigned int nbr)
{
	if (nbr / 10 != 0)
		ft_putnbr_uns(nbr / 10);
	ft_putchar_fd(nbr % 10 + '0', 1);
}

void	ft_putnbr_hex(unsigned int nbr, char specifier)
{
	char	*base;

	if (specifier == 'x')
		base = "0123456789abcdef";
	else
		base = "0123456789ABCDEF";
	if (nbr / 16 != 0)
		ft_putnbr_hex(nbr / 16, specifier);
	ft_putchar_fd(base[nbr % 16], 1);
}

int	ft_putnbr_hex_long(unsigned long nbr, int *count)
{
	char	*base;

	base = "0123456789abcdef";
	if (nbr / 16 != 0)
		ft_putnbr_hex_long(nbr / 16, count);
	ft_putchar_fd(base[nbr % 16], 1);
	*count += 1;
	return (*count);
}
