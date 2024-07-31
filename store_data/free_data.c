/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 13:16:26 by ftanon            #+#    #+#             */
/*   Updated: 2024/07/31 17:22:13 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_data(t_data	*data)
{
	// printf("%s\n", data->exit_string);
	if (data->all_paths)
		free_array(data->all_paths);
	free(data);
}
