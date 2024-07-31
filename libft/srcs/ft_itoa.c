/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 10:25:39 by rrichard          #+#    #+#             */
/*   Updated: 2024/01/09 18:12:17 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static char	*ft_negitoa(int n)
{
	char	*str;
	int		i;
	int		nb;

	i = 0;
	nb = n;
	if (n == 0)
		return (ft_strdup("0"));
	while (nb)
	{
		nb /= 10;
		i++;
	}
	str = malloc(sizeof(char) * (i + 2));
	if (!(str))
		return (NULL);
	str[i + 1] = '\0';
	str[0] = '-';
	while (i > 0)
	{
		str[i] = -(n % 10) + '0';
		n /= 10;
		i--;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		i;
	int		nb;

	i = 0;
	nb = n;
	if (n <= 0)
		return (ft_negitoa(n));
	while (nb)
	{
		nb /= 10;
		i++;
	}
	str = malloc(sizeof(char) * (i + 1));
	if (!(str))
		return (NULL);
	str[i] = '\0';
	nb = n;
	while (i > 0)
	{
		str[i - 1] = nb % 10 + '0';
		nb /= 10;
		i--;
	}
	return (str);
}

/* int		main(int ac, char **av)
{
	if (ac == 2)
	{
		printf("%s\n", ft_itoa(atoi(av[1])));
	}
	return (0);
} */
