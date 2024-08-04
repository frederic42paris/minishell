/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 19:09:42 by sumseo            #+#    #+#             */
/*   Updated: 2024/08/04 12:41:10 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	func_pwd(t_data *data)
{
	char	cwd[4096];

	if (data->num_cmd < 2)
	{
		getcwd(cwd, sizeof(cwd));
		ft_putendl_fd(cwd, data->fd_stdout);
		return (EXIT_SUCCESS);
	}
	ft_putendl_fd("pwd: too many arguments", STDERR_FILENO);
	return (EXIT_FAILURE);
}
