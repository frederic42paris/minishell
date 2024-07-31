/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 19:11:21 by sumseo            #+#    #+#             */
/*   Updated: 2024/07/31 14:00:58 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	func_env(t_parse *cmds, char **environ)
{
	int	i;

	i = 0;
	if (cmds->cmd_array[1])
		return (ft_putendl_fd("env: too many arguments",
				STDERR_FILENO), EXIT_FAILURE);
	else
	{
		while (environ[i] != NULL)
		{
			printf("%s\n", environ[i]);
			i++;
		}
		return (0);
	}
}
