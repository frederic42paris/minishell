/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 14:02:33 by rrichard          #+#    #+#             */
/*   Updated: 2023/12/08 16:07:52 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	ft_format_x(va_list *args, t_format_specifier fs)
{
	fs.value = va_arg(*args, unsigned int);
	fs.count = 0;
	if (ft_strchr(fs.flags, '#') && fs.value != 0)
	{
		ft_putstr_fd("0x", 1);
		fs.count = 2;
	}
	ft_putnbr_hex(fs.value, 'x');
	return (ft_count_digits_hex(fs.value) + fs.count);
}

int	ft_format_xl(va_list *args, t_format_specifier fs)
{
	fs.value = va_arg(*args, unsigned int);
	fs.count = 0;
	if (ft_strchr(fs.flags, '#') && fs.value != 0)
	{
		ft_putstr_fd("0X", 1);
		fs.count = 2;
	}
	ft_putnbr_hex(fs.value, 'X');
	return (ft_count_digits_hex(fs.value) + fs.count);
}

int	ft_format_p(va_list *args, t_format_specifier fs)
{
	void			*ptr_value;
	unsigned long	value;

	ptr_value = va_arg(*args, void *);
	value = (unsigned long)ptr_value;
	fs.count = 0;
	if (value == 0)
	{
		ft_putstr_fd("(nil)", 1);
		return (5);
	}
	ft_putstr_fd("0x", 1);
	ft_putnbr_hex_long(value, &fs.count);
	return (fs.count + 2);
}

int	ft_format_percent(va_list *args, t_format_specifier fs)
{
	(void)args;
	(void)fs;
	ft_putchar_fd('%', 1);
	return (1);
}
