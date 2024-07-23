/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 19:11:21 by sumseo            #+#    #+#             */
/*   Updated: 2024/07/23 12:19:58 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	func_env(t_parse *cmds, t_env **env, char **environ)
{
	(void)env;
	int	i;

	i = 0;
	if (cmds->cmd_array[1])
		printf("env: too many arguments\n");
	else
	{
		while (environ[i] != NULL)
		{
			printf("%s\n", environ[i]);
			i++;
		}
	}
}
