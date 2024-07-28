/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 11:37:19 by ftanon            #+#    #+#             */
/*   Updated: 2024/07/28 17:12:11 by ftanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_input(char const *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '"')
		{
			i++;
			while (not_double_quote(str[i]))
				i++;
			if (str[i] == '\0')
			{
				printf("Error : Double quotes unclosed\n");
				return (1);
			}
		}
		else if (str[i] == 39)
		{
			i++;
			while (not_single_quote(str[i]))
				i++;
			if (str[i] == '\0')
			{
				printf("Error : Single quotes unclosed\n");
				return (1);
			}
		}
		i++;
	}
	i = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] == '\0')
		return (1);
	return (0);
}
