/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/07/31 18:25:02 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

void	export_without_args(t_env *env_list)
{
	while (env_list)
	{
		printf("declare -x \"%s\"\n", env_list->env_var);
		env_list = env_list->next;
	}
}

void	update_existing_env(char *env_str, char *name, char ***environ)
{
	int	i;

	i = 0;
	while (*environ[i])
	{
		if (!ft_strncmp(*environ[i], name, ft_strlen(name))
			&& *environ[i][ft_strlen(name)] == '=')
		{
			free(*environ[i]);
			*environ[i] = ft_strdup(env_str);
		}
		i++;
	}
}

t_env	*find_env_var(char *name, t_env *env)
{
	char	*str;

	while (env)
	{
		str = env->env_var;
		if (!ft_strncmp(str, name, ft_strlen(name))
			&& (str[ft_strlen(name)] == '=' || str[ft_strlen(name) == '\0']))
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
		existing_env->env_var = ft_strdup(env_str);
	}
}

int	export_with_args(t_parse *cmds, t_env **env_list)
{
	int		i;
	char	*cmd_cpy;
	char	*var_name;
	char	*equals;

	i = 1;
	while (cmds->cmd_array[i])
	{
		cmd_cpy = ft_strdup(cmds->cmd_array[i]);
		equals = ft_strchr(cmd_cpy, '=');
		if (!equals)
		{
			if (!find_env_var(cmd_cpy, *env_list))
				push_env_list(env_list, cmds->cmd_array[i]);
		}
		else
		{
			*equals = '\0';
			var_name = ft_strdup(cmd_cpy);
			ft_setenv(cmds->cmd_array[i], var_name, env_list);
			free(var_name);
		}
		free(cmd_cpy);
		i++;
	}
	return (0);
}


int	func_export(t_parse *cmds, t_env **env_list)
{
	int	i;

	i = 1;
	if (!cmds->cmd_array[i])
		export_without_args(*env_list);
	else
		export_with_args(cmds, env_list);
	return (0);
}
