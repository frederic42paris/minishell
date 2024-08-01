/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 19:11:21 by sumseo            #+#    #+#             */
/*   Updated: 2024/08/01 11:45:00 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	func_env(t_parse *cmds, t_env *env_list)
{
	if (cmds->cmd_array[1])
		return (ft_putendl_fd("env: too many arguments",
				STDERR_FILENO), EXIT_FAILURE);
	else
	{
		while (env_list)
		{
			printf("%s\n", env_list->env_var);
			env_list = env_list->next;
		}
	}
	return (0);
}
