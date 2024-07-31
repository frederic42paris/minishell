/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 15:00:04 by rrichard          #+#    #+#             */
/*   Updated: 2024/01/15 09:24:44 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int	i;

	i = 0;
	if (s == NULL)
		return ;
	while (s[i])
	{
		(*f)(i, &s[i]);
		i++;
	}
}

/* #include <stdio.h>

void	uppercase(unsigned int index, char *c)
{
	(void)index;
	if (*c >= 'a' && *c <= 'z')
		*c -= 32;
}

int	main(int ac, char **av)
{
	if (ac == 2)
	{
		ft_striteri(av[1], &uppercase);
		printf("%s\n", av[1]);
	}
	return (0);
} */
