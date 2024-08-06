/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_multipipe.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 16:03:39 by rrichard          #+#    #+#             */
/*   Updated: 2024/08/06 16:55:43 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_bool	check_paths(t_parse *cmds)
{
	while (cmds)
	{
		if (cmds->path)
		{
			if (!is_builtin(cmds))
			{
				free(cmds->cmd_array[0]);
				cmds->cmd_array[0] = ft_shield_strdup(cmds->path);
			}
		}
		cmds = cmds->next;
	}
	return (EXIT_SUCCESS);
}
