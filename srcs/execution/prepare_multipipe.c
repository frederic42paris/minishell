/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_multipipe.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 16:03:39 by rrichard          #+#    #+#             */
/*   Updated: 2024/07/26 16:08:26 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	check_paths(t_parse *cmds)
{
	while (cmds)
	{
		if (!cmds->path)
			return ((void)printf("minishell: command not found: %s\n",
					cmds->cmd_array[0]), EXIT_FAILURE);
		free(cmds->cmd_array[0]);
		cmds->cmd_array[0] = ft_strdup(cmds->path);
		cmds = cmds->next;
	}
	return (EXIT_SUCCESS);
}

int	count_cmds(t_parse *cmds)
{
	int	res;

	res = 0;
	while (cmds)
	{
		if (cmds->path)
			res++;
		cmds = cmds->next;
	}
	return (res);
}

void	prepare_in_out(t_parse *cmds, t_data *data, int (**fd)[2])
{
	int		check;
	t_parse	*last;

	check = exec_check_redirection(cmds, data->num_cmd);
	last = cmds;
	if (check == 3 || check == 1)
	{
		(*fd)[0][0] = open(cmds->redirection->name, O_RDONLY);
		if ((*fd)[0][0] < 0)
			perror(cmds->redirection->name);
	}
	else
		(*fd)[0][0] = STDIN_FILENO;
	if (check == 3 || check == 2)
	{
		while (last->next != NULL)
			last = last->next;
		(*fd)[0][1] = open(last->redirection->name,
				O_CREAT | O_RDWR | O_TRUNC, 0644);
	}
	else
		(*fd)[0][1] = STDOUT_FILENO;
}
