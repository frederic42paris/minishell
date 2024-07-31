/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtol.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 11:55:14 by rrichard          #+#    #+#             */
/*   Updated: 2024/06/26 14:09:00 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include <limits.h>
#include <stdio.h>
#include <ctype.h>

int	parse_strtol(const char **nptr, int *base)
{
	int			i;
	int			sign;

	i = 0;
	sign = 0;
	while ((*nptr[i] >= 9 && *nptr[i] <= 13) || *nptr[i] == ' ')
	{
		printf("%c |", (*nptr)[i]);
		i++;
	}
	if (*nptr[i] == '+' || *nptr[i] == '-')
		if (*nptr[i++] == '-')
			sign = 1;
	if ((*base == 0 || *base == 16)
		&& (*nptr)[i] == '0' && ((*nptr)[i + 1] == 'x' || (*nptr)[i + 1] == 'X')
		&& (((*nptr)[i + 2] >= '0' && (*nptr)[i + 2] <= '9')
			|| ((*nptr)[i + 2] >= 'A' && (*nptr)[i + 2] <= 'F')
			|| ((*nptr)[i + 2] >= 'a' && (*nptr)[i + 2] <= 'f')))
	{
		i += 2;
		*base = 16;
	}
	if (*base == 0)
	{
		if (*nptr[i] == '0')
			*base = 8;
		else
			*base = 10;
	}
	*nptr += i;
	return (sign);
}

long	ft_strtol(const char *nptr, char **endptr, int base)
{
	char			c;
	int				neg, any, cutlim;
	unsigned long	cutoff;
	unsigned long	acc;

	neg = parse_strtol(&nptr, &base);
	any = 0;
	acc = any;
	if (base < 2 || base > 36)
		return (0);
	if (neg)
		cutoff = (unsigned long)-(LONG_MIN + LONG_MAX) + LONG_MAX;
	else
		cutoff = LONG_MAX;
	cutlim = cutoff % base;
	cutoff /= base;
	while (1)
	{
		c = *nptr++;
		if (c >= '0' && c <= '9')
			c -= '0';
		else if (c >= 'A' && c <= 'Z')
			c -= 'A' - 10;
		else if (c >= 'a' && c <= 'z')
			c -= 'a' - 10;
		else
			break ;
		if (c >= base)
			break ;
		if ((any < 0) || acc > cutoff || (acc == cutoff && c > cutlim))
			any = -1;
		else
		{
			any = 1;
			acc *= base;
			acc += c;
		}
	}
	if (any < 0)
	{
		if (neg)
			acc = LONG_MIN;
		else
			acc = LONG_MAX;
	}
	else if (!any)
		return (-1);
	else
	{
		if (neg)
			acc = -acc;
	}
	if (endptr != NULL)
	{
		if (any)
			*endptr = (char *)(nptr - 1);
		else
			*endptr = (char *)nptr;
	}
	return (acc);
}
