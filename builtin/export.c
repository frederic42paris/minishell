/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 11:45:47 by rrichard          #+#    #+#             */
/*   Updated: 2024/08/06 18:35:53 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	export_without_args(t_env *env_list, t_data *data)
{
	env_list = sort_env(env_list, env_list);
	while (env_list)
	{
		ft_putstr_fd("declare -x \"", data->fd_stdout);
		ft_putstr_fd(env_list->env_var, data->fd_stdout);
		ft_putendl_fd("\"", data->fd_stdout);
		env_list = env_list->next;
	}
}

t_env	*find_env_var(char *name, t_env *env)
{
	char	*str;

	while (env)
	{
		str = env->env_var;
		if (!ft_strncmp(str, name, ft_strlen(name))
			&& (str[ft_strlen(name)] == '='))
			return (env);
		env = env->next;
	}
	return (NULL);
}

void	ft_setenv(char *env_str, char *name, t_env **env_list)
{
	t_env	*existing_env;

	existing_env = find_env_var(name, *env_list);
	if (existing_env)
	{
		free(existing_env->env_var);
		existing_env->env_var = ft_shield_strdup(env_str);
	}
	else
		push_env_list(env_list, env_str);
}

void	export_with_args(t_parse *cmds, t_env **env_list)
{
	int		i;
	char	*cmd_cpy;
	char	*var_name;
	char	*equals;

	i = 1;
	while (cmds->cmd_array[i])
	{
		cmd_cpy = ft_shield_strdup(cmds->cmd_array[i]);
		equals = ft_strchr(cmd_cpy, '=');
		if (!equals)
		{
			if (!find_env_var(cmd_cpy, *env_list))
				push_env_list(env_list, cmds->cmd_array[i]);
		}
		else
		{
			*equals = '\0';
			var_name = ft_shield_strdup(cmd_cpy);
			ft_setenv(cmds->cmd_array[i], var_name, env_list);
			free(var_name);
		}
		free(cmd_cpy);
		i++;
	}
}

int	func_export(t_parse *cmds, t_env **env_list, t_data *data)
{
	if (!cmds->cmd_array[1])
		export_without_args(*env_list, data);
	else
		export_with_args(cmds, env_list);
	if (data->fd_stdin != STDIN_FILENO)
		close(data->fd_stdin);
	if (data->fd_stdout != STDOUT_FILENO)
		close(data->fd_stdout);
	return (0);
}
