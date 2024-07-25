/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_formats.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 12:51:12 by rrichard          #+#    #+#             */
/*   Updated: 2023/12/08 16:07:49 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	ft_format_d(va_list *args, t_format_specifier fs)
{
	fs.value = va_arg(*args, int);
	fs.count = 0;
	fs.hex = 0;
	if (ft_strchr(fs.flags, '+') && fs.value >= 0)
	{
		ft_putchar_fd('+', 1);
		fs.count = 1;
	}
	else if (ft_strchr(fs.flags, ' ') && fs.value >= 0)
	{
		ft_putchar_fd(' ', 1);
		fs.count = 1;
	}
	ft_putnbr_fd(fs.value, 1);
	return (ft_count_digits(fs.value) + fs.count);
}

int	ft_format_s(va_list *args, t_format_specifier fs)
{
	char	*value;

	(void)fs;
	value = va_arg(*args, char *);
	if (!(value))
		value = "(null)";
	ft_putstr_fd(value, 1);
	return (ft_strlen(value));
}

int	ft_format_c(va_list *args, t_format_specifier fs)
{
	char	value;

	(void)fs;
	value = va_arg(*args, int);
	ft_putchar_fd(value, 1);
	return (1);
}

int	ft_format_u(va_list *args, t_format_specifier fs)
{
	fs.value = va_arg(*args, unsigned int);
	fs.count = 0;
	fs.hex = 0;
	ft_putnbr_uns(fs.value);
	return (ft_count_digits_uns(fs.value) + fs.count);
}
