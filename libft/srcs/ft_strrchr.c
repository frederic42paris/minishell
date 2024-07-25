/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 14:56:16 by rrichard          #+#    #+#             */
/*   Updated: 2024/01/09 18:12:53 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strrchr(char *str, int c)
{
	char	*last;

	last = 0;
	while (*str)
	{
		if (*str == c)
			last = str;
		str++;
	}
	if (c == '\0')
		return (str);
	return (last);
}
