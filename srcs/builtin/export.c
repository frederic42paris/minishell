/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 19:11:10 by sumseo            #+#    #+#             */
/*   Updated: 2024/07/22 14:54:16 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export_without_args(t_env **env)
{
	t_env	*env_copy;
	t_env	*current;

	current = *env;
	env_copy = NULL;
	while (current)
	{
		push_env_list(&env_copy, current->env_var, ft_strlen(current->env_var));
		current = current->next;
	}
	current = sort_env(env_copy, current);
	while (current)
	{
		printf("%s\n", current->env_var);
		current = current->next;
	}
}

void	update_existing_env(char *env_str, char *name, t_env **env)
{
	t_env	*current;

	current = *env;
	while (current != NULL)
	{
		if (ft_strncmp(current->env_var, name, ft_strlen(name)) == 0)
		{
			free(current->env_var);
			current->env_var = ft_strdup(env_str);
		}
		current = current->next;
	}
}

char	*find_env_var(char *name, t_env **env)
{
	t_env	*current;

	current = *env;
	while (current != NULL)
	{
		if (ft_strncmp(current->env_var, name, ft_strlen(name)) == 0
			&& current->env_var[ft_strlen(name)] == '=')
			return (current->env_var);
		current = current->next;
	}
	return (NULL);
}

void	ft_setenv(char *env_str, char *name, t_env **env)
{
	char	*existing_env;

	existing_env = find_env_var(name, env);
	if (existing_env)
		update_existing_env(env_str, name, env);
	else
		push_env_list(env, env_str, ft_strlen(env_str));
}

void	func_export(t_parse *cmds, t_env **env)
{
	char	*var_name;
	char	*equals;
	char	*cmd_cpy;
	int		i;

	i = 1;
	if (!cmds->cmd_array[i])
		return (export_without_args(env));
	while (cmds->cmd_array[i])
	{
		var_name = ft_strdup(cmds->cmd_array[i]);
		equals = ft_strchr(var_name, '=');
		if (!equals)
			ft_setenv(cmd_cpy, "", env);
		else
		{
			*equals = '\0';
			cmd_cpy = ft_strdup(cmds->cmd_array[i]);
			ft_setenv(cmd_cpy, var_name, env);
			free(var_name);
			free(cmd_cpy);
		}
		i++;
	}
}
