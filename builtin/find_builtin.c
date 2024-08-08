/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 18:41:15 by sumseo            #+#    #+#             */
/*   Updated: 2024/08/08 15:25:03 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exec_builtin(t_parse *cmds, t_data *data, t_env **env_list)
{
	if (!ft_strcmp(cmds->cmd_array[0], "echo"))
		return (func_echo(cmds, data));
	else if (!ft_strcmp(cmds->cmd_array[0], "pwd"))
		return (func_pwd(cmds, data));
	else if (!ft_strcmp(cmds->cmd_array[0], "cd"))
		return (func_cd(cmds, data));
	else if (!ft_strcmp(cmds->cmd_array[0], "env"))
		return (func_env(cmds, *env_list, data));
	else if (!ft_strcmp(cmds->cmd_array[0], "exit"))
		return (func_exit(cmds, data));
	else if (!ft_strcmp(cmds->cmd_array[0], "unset"))
		return (func_unset(cmds, env_list, data));
	else if (!ft_strcmp(cmds->cmd_array[0], "export"))
		return (func_export(cmds, env_list, data));
	else
		return (0);
}

int	is_builtin(t_parse *cmds)
{
	if (!ft_strcmp(cmds->cmd_array[0], "echo")
		|| !ft_strcmp(cmds->cmd_array[0], "pwd")
		|| !ft_strcmp(cmds->cmd_array[0], "cd")
		|| !ft_strcmp(cmds->cmd_array[0], "env")
		|| !ft_strcmp(cmds->cmd_array[0], "exit")
		|| !ft_strcmp(cmds->cmd_array[0], "unset")
		|| !ft_strcmp(cmds->cmd_array[0], "export"))
		return (1);
	return (0);
}
