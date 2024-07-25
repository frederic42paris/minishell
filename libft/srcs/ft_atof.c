/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 15:23:16 by rrichard          #+#    #+#             */
/*   Updated: 2024/02/06 15:52:50 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

//Converts the initial portion of the string pointed to by str to double
double	ft_atof(const char *str)
{
	int		i;
	int		sign;
	int		dx;
	double	nb;

	i = 0;
	sign = 1;
	nb = 0.0;
	dx = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			sign *= -1;
	while (str[i] >= '0' && str[i] <= '9')
		nb = (nb * 10) + (str[i++] - '0');
	if (str[i] == ',' || str[i] == '.')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = (nb * 10) + (str[i++] - '0');
		dx *= 10;
	}
	return (nb * sign / dx);
}
