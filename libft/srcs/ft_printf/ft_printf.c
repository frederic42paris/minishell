/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 14:46:18 by rrichard          #+#    #+#             */
/*   Updated: 2023/12/08 16:07:42 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

size_t	parse_format_specifier(const char *s, t_format_specifier *fs, size_t *i)
{
	size_t	len;

	fs->flags[0] = 0;
	*i += 1;
	len = 0;
	if (ft_isdigit(s[*i]) || (!ft_strchr("+ #", s[*i])
			&& !ft_strchr("cspdiuxX%", s[*i])))
		return (0);
	while (ft_strchr("+ #", s[*i]))
	{
		len = ft_strlen(fs->flags);
		fs->flags[len] = s[*i];
		fs->flags[len + 1] = '\0';
		*i += 1;
	}
	if (ft_isdigit(s[*i]))
		return (0);
	if ((ft_strchr(fs->flags, ' ')
			&& s[*i] == 's') || !ft_strchr("cspdiuxX%", s[*i]))
		return (0);
	fs->specifier = s[*i];
	return (*i + 1);
}

t_format_func	get_format_func(char specifier)
{
	if (specifier == 'd')
		return (ft_format_d);
	else if (specifier == 'i')
		return (ft_format_d);
	else if (specifier == 's')
		return (ft_format_s);
	else if (specifier == 'c')
		return (ft_format_c);
	else if (specifier == 'u')
		return (ft_format_u);
	else if (specifier == 'x')
		return (ft_format_x);
	else if (specifier == 'X')
		return (ft_format_xl);
	else if (specifier == 'p')
		return (ft_format_p);
	else if (specifier == '%')
		return (ft_format_percent);
	else
		return (NULL);
}

int	ft_parse(char c)
{
	ft_putchar_fd(c, 1);
	return (1);
}

int	ft_error(const char *s, t_format_specifier *fs)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i] != '%')
			i++;
		else
		{
			i = parse_format_specifier(s, fs, &i);
			if (i == 0)
			{
				ft_putstr_fd("Error\n", 2);
				return (0);
			}
		}
	}
	return (1);
}

int	ft_printf(const char *s, ...)
{
	va_list				args;
	size_t				i;
	t_format_specifier	fs;
	int					len;
	t_format_func		func;

	i = 0;
	len = 0;
	va_start(args, s);
	if (!s || ft_error(s, &fs) == 0)
		return (-1);
	while (s[i])
	{
		if (s[i] != '%')
			len += ft_parse(s[i++]);
		else
		{
			i = parse_format_specifier(s, &fs, &i);
			func = get_format_func(fs.specifier);
			if (func != NULL)
				len += func(&args, fs);
		}
	}
	va_end(args);
	return (len);
}
