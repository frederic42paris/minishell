/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 11:15:54 by rrichard          #+#    #+#             */
/*   Updated: 2024/05/02 12:55:48 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

size_t	ft_strlen(char const *str)
{
	size_t	len;

	len = 0;
	if (str == NULL)
		return (0);
	while (str[len])
		len++;
	return (len);
}
