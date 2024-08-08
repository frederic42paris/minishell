/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 17:24:11 by rrichard          #+#    #+#             */
/*   Updated: 2024/08/08 17:19:18 by rrichard         ###   ########.fr       */
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

void	free_fail(t_parse *cmds, t_data *data)
{
	free_env_list(&data->env);
	while (cmds->prev)
		cmds = cmds->prev;
	free_parse_list(&cmds);
	free_data(data);
}

void	exit_error(t_parse *cmds, t_data *data)
{
	if (errno == ENOENT)
	{
		ft_putstr_fd("command not found: ", STDERR_FILENO);
		ft_putendl_fd(cmds->cmd_array[0], STDERR_FILENO);
		free_exec(data->fd, data->pid, NULL);
		free_fail(cmds, data);
		exit(127);
	}
	else
	{
		free_exec(data->fd, data->pid, "execve");
		free_fail(cmds, data);
		exit(1);
	}
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
