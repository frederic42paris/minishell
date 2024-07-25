/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 11:02:51 by rrichard          #+#    #+#             */
/*   Updated: 2023/12/08 16:06:59 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include "libft.h"

//Structure to store the format specifier
typedef struct s_format_specifier
{
	char	flags[6];
	long	value;
	int		width;
	int		count;
	char	specifier;
	int		hex;
}	t_format_specifier;

//Function pointer to the format functions
typedef int	(*t_format_func)(va_list *args, t_format_specifier fs);

int					ft_format_d(va_list *args, t_format_specifier fs);
int					ft_format_s(va_list *args, t_format_specifier fs);
int					ft_format_c(va_list *args, t_format_specifier fs);
int					ft_format_u(va_list *args, t_format_specifier fs);
int					ft_format_x(va_list *args, t_format_specifier fs);
int					ft_format_xl(va_list *args, t_format_specifier fs);
int					ft_format_p(va_list *args, t_format_specifier fs);
int					ft_format_percent(va_list *args, t_format_specifier fs);
int					ft_printf(const char *format, ...);
//Function to parse the format specifier
size_t				parse_format_specifier(const char *format,
						t_format_specifier *fs, size_t *i);
//Function to get the format function
t_format_func		get_format_func(char specifier);
void				ft_putnbr_hex(unsigned int nbr, char specifier);
void				ft_putnbr_uns(unsigned int nbr);
int					ft_putnbr_hex_long(unsigned long nbr, int *count);
int					ft_count_digits(int n);
int					ft_count_digits_uns(unsigned int n);
int					ft_count_digits_hex(unsigned int n);
int					ft_parse(char c);

#endif