/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_multipipe.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 16:03:39 by rrichard          #+#    #+#             */
/*   Updated: 2024/08/04 17:26:03 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_bool	check_paths(t_parse *cmds)
{
	while (cmds)
	{
		if (cmds->path)
		{
			free(cmds->cmd_array[0]);
			cmds->cmd_array[0] = ft_strdup(cmds->path);
		}
		else if (!(cmds->cmd_array[0][0] == '.'
			|| cmds->cmd_array[0][0] == '/'))
		{
			if (access(cmds->cmd_array[0], X_OK) != 0)
			{
				ft_putstr_fd("command not found: ", STDERR_FILENO);
				ft_putendl_fd(cmds->cmd_array[0], STDERR_FILENO);
			}
			return (EXIT_FAILURE);
		}
		cmds = cmds->next;
	}
	return (EXIT_SUCCESS);
}
