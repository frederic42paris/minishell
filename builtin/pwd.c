/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 19:09:42 by sumseo            #+#    #+#             */
/*   Updated: 2024/08/06 16:19:46 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	func_pwd(t_parse *cmds, t_data *data)
{
	char	cwd[4096];

	if (!cmds->cmd_array[1])
	{
		getcwd(cwd, sizeof(cwd));
		ft_putendl_fd(cwd, data->fd_stdout);
		return (EXIT_SUCCESS);
	}
	ft_putendl_fd("pwd: too many arguments", STDERR_FILENO);
	return (EXIT_FAILURE);
}
