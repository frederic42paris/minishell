/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 19:11:15 by sumseo            #+#    #+#             */
/*   Updated: 2024/07/23 12:14:02 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	func_unset(t_parse *cmds, t_env **env, char ***environ)
{
	int		i;
	char	*existing_env;

	i = 1;
	if (environ)
	{
		if (!cmds->cmd_array[i])
			return ((void)printf("unset: not enough arguments\n"));
		else
		{
			while (cmds->cmd_array[i])
			{
				existing_env = find_env_var(cmds->cmd_array[i], env);
				if (existing_env != NULL)
					delete_one_env(env, cmds->cmd_array[1]);
				i++;
			}
		}
	}
}
