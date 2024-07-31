/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 09:07:10 by rrichard          #+#    #+#             */
/*   Updated: 2024/01/15 09:24:44 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	c;
	int		sign;

	sign = 1;
	if (n < 0)
	{
		write(fd, "-", 1);
		sign *= -1;
	}
	if (n / 10)
		ft_putnbr_fd(n / 10 * sign, fd);
	c = n % 10 * sign + '0';
	write(fd, &c, 1);
}
