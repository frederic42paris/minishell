/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 17:24:11 by rrichard          #+#    #+#             */
/*   Updated: 2024/08/08 12:35:02 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_exec(int (**fd)[2], pid_t **pid, char *str)
{
	free(*fd);
	free(*pid);
	if (str)
		perror(str);
	return ;
}

void	wait_loop(pid_t *pid, t_data *data)
{
	int	i;
	int	status;

	i = 0;
	while (i < data->num_cmd)
	{
		waitpid(pid[i], &status, 0);
		if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
		{
			data->exit_status = WEXITSTATUS(status);
			break ;
		}
		i++;
	}
}
