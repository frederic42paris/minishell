/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 19:11:21 by sumseo            #+#    #+#             */
/*   Updated: 2024/07/19 17:35:37 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	func_env(t_parse *cmds, t_env **env)
{
	if (cmds->cmd_array[1])
		printf("env: too many arguments\n");
	else
		display_env_list(*env);
}
