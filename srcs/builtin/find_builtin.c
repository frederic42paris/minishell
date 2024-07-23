/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 18:41:15 by sumseo            #+#    #+#             */
/*   Updated: 2024/07/23 12:08:09 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(t_parse *cmds)
{
	if (!ft_strcmp(cmds->cmd_array[0], "echo"))
		return (1);
	else if (!ft_strcmp(cmds->cmd_array[0], "pwd"))
		return (2);
	else if (!ft_strcmp(cmds->cmd_array[0], "cd"))
		return (3);
	else if (!ft_strcmp(cmds->cmd_array[0], "env"))
		return (4);
	else if (!ft_strcmp(cmds->cmd_array[0], "exit"))
		return (5);
	else if (!ft_strcmp(cmds->cmd_array[0], "unset"))
		return (6);
	else if (!ft_strcmp(cmds->cmd_array[0], "export"))
		return (7);
	else
		return (0);
}

void	exec_builtin(int func, t_parse *cmds, t_env **env, char ***environ)
{
	if (func == 1)
		func_echo(cmds);
	else if (func == 2)
		func_pwd(cmds);
	else if (func == 3)
		func_cd(cmds->cmd_array[1]);
	else if (func == 4)
		func_env(cmds, env, *environ);
	else if (func == 5)
		func_exit(cmds);
	else if (func == 6)
		func_unset(cmds, env, environ);
	else if (func == 7)
		func_export(cmds, env, environ);
}
