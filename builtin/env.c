/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 19:11:21 by sumseo            #+#    #+#             */
/*   Updated: 2024/08/06 18:35:44 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	func_env(t_parse *cmds, t_env *env_list, t_data *data)
{
	if (cmds->cmd_array[1])
		return (ft_putendl_fd("env: too many arguments",
				STDERR_FILENO), EXIT_FAILURE);
	else
	{
		while (env_list)
		{
			ft_putendl_fd(env_list->env_var, data->fd_stdout);
			env_list = env_list->next;
		}
	}
	if (data->fd_stdin != STDIN_FILENO)
		close(data->fd_stdin);
	if (data->fd_stdout != STDOUT_FILENO)
		close(data->fd_stdout);
	return (0);
}
