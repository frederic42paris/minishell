/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_multipipe.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 16:03:39 by rrichard          #+#    #+#             */
/*   Updated: 2024/08/08 17:52:13 by rrichard         ###   ########.fr       */
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
		if (!cmds->cmd_array[0])
			return (EXIT_FAILURE);
		cmds = cmds->next;
	}
	return (EXIT_SUCCESS);
}
