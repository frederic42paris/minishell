/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtol.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 11:55:14 by rrichard          #+#    #+#             */
/*   Updated: 2024/06/27 10:20:51 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

t_bool	check_hex(const char *nptr, int base)
{
	int	i;

	i = 0;
	if ((base == 0 || base == 16)
		&& nptr[i] == '0' && (nptr[i + 1] == 'x' || nptr[i + 1] == 'X')
		&& ((nptr[i + 2] >= '0' && nptr[i + 2] <= '9')
			|| (nptr[i + 2] >= 'A' && nptr[i + 2] <= 'F')
			|| (nptr[i + 2] >= 'a' && nptr[i + 2] <= 'f')))
		return (TRUE);
	return (FALSE);
}

int	parse_strtol(const char **nptr, int *base)
{
	int			i;
	int			sign;

	i = 0;
	sign = 0;
	while (ft_isspace((unsigned char)(*nptr)[i]))
		i++;
	if ((*nptr)[i] == '+' || (*nptr)[i] == '-')
		if ((*nptr)[i++] == '-')
			sign = 1;
	if (check_hex((*nptr) + i, *base))
	{
		i += 2;
		*base = 16;
	}
	if (*base == 0)
	{
		if ((*nptr)[i] == '0')
			*base = 8;
		else
			*base = 10;
	}
	*nptr += i;
	return (sign);
}

void	loop_nptr(const char **nptr, unsigned long *acc, t_cuts *data, int base)
{
	char			c;

	while (1)
	{
		c = *(*nptr)++;
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
		if ((data->any < 0) || *acc > data->cutoff
			|| (*acc == data->cutoff && c > data->cutlim))
			data->any = -1;
		else
		{
			data->any = 1;
			*acc *= base;
			*acc += c;
		}
	}
}

void	end_strtol(t_cuts data, unsigned long *acc)
{
	if (data.any < 0)
	{
		if (data.neg)
			*acc = LONG_MIN;
		else
			*acc = LONG_MAX;
	}
	else if (!data.any)
		*acc = 0;
	else
	{
		if (data.neg)
			*acc *= -1;
	}
}

long	ft_strtol(const char *nptr, char **endptr, int base)
{
	unsigned long	acc;
	t_cuts			data;

	data.neg = parse_strtol(&nptr, &base);
	data.any = 0;
	acc = data.any;
	if (base < 2 || base > 36)
		return (0);
	if (data.neg)
		data.cutoff = (unsigned long)-(LONG_MIN + LONG_MAX) + LONG_MAX;
	else
		data.cutoff = LONG_MAX;
	data.cutlim = data.cutoff % base;
	data.cutoff /= base;
	loop_nptr(&nptr, &acc, &data, base);
	end_strtol(data, &acc);
	if (endptr != NULL)
	{
		if (data.any)
			*endptr = (char *)(nptr - 1);
		else
			*endptr = (char *)nptr;
	}
	return (acc);
}
