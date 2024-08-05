/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shield.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 10:21:44 by rrichard          #+#    #+#             */
/*   Updated: 2024/08/05 10:31:41 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_shield_strdup(const char *str)
{
	char	*res;

	res = ft_strdup(str);
	if (res == NULL)
	{
		perror("Malloc error");
		exit(EXIT_FAILURE);
	}
	return (res);
}
