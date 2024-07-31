/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 18:41:15 by sumseo            #+#    #+#             */
/*   Updated: 2024/07/31 17:35:57 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

int	exec_builtin(int func, t_parse *cmds, t_data *data, t_env **env_list)
{
	if (func == 1)
		return (func_echo(cmds));
	else if (func == 2)
		return (func_pwd(cmds, data));
	else if (func == 3)
		return (func_cd(cmds));
	else if (func == 4)
		return (func_env(cmds, *env_list));
	else if (func == 5)
		return (func_exit(cmds));
	// else if (func == 6)
	// 	func_unset(cmds, environ);
	else if (func == 7)
		return (func_export(cmds, env_list));
	return (0);
}
