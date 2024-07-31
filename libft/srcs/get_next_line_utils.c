/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 09:13:48 by rrichard          #+#    #+#             */
/*   Updated: 2024/04/17 09:14:17 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*create_line(char *line, char **static_storage, char *buffer)
{
	char	*tmp_line;

	if (*static_storage)
	{
		tmp_line = ft_strjoin(*static_storage, buffer);
		line = ft_strjoin(tmp_line, "\n");
		free(*static_storage);
		free(tmp_line);
	}
	else
	{
		tmp_line = ft_strdup(buffer);
		line = ft_strjoin(tmp_line, "\n");
		free(tmp_line);
	}
	return (line);
}
