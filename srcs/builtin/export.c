/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 19:11:10 by sumseo            #+#    #+#             */
/*   Updated: 2024/07/18 09:10:24 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*sort_env(t_env *env_copy, t_env *current)
{
	int		swapped;
	char	*tmp;

	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		current = env_copy;
		while (current && current->next != NULL)
		{
			if (ft_strncmp(current->env_var, current->next->env_var, 1) > 0)
			{
				tmp = current->env_var;
				current->env_var = current->next->env_var;
				current->next->env_var = tmp;
				swapped = 1;
			}
			current = current->next;
		}
	}
	current = env_copy;
	return (current);
}

void	export_without_args(t_env **env)
{
	t_env	*env_copy;
	t_env	*current;

	// display_env_list(*env);
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
		// printf("export %s\n", current->env_var);
		current = current->next;
	}
}

int	check_variable(t_env **env, char *variable, char *value)
{
	char	*found_value;
	int		result;
	t_env	*current;

	result = 0;
	current = *env;
	while (current != NULL)
	{
		found_value = ft_strnstr(current->env_var, variable,
				strlen(current->env_var));
		if (found_value != NULL)
		{
			result = 1;
			replace_one_env(env, current->env_var, variable, value);
			break ;
		}
		current = current->next;
	}
	return (result);
}

t_bool	update_existing_env(char *env_str, char *name, t_env **env)
{
	
}

void	ft_setenv(char *env_str, char *name, char *value, t_env **env)
{
	char	*env_str;
	char	*existing_env;
	size_t	env_count;
	char	**new_env;

	existing_env = getenv(name);
	if (existing_env)
	{
		if (update_existing_env(env_str, name, env))
	}
}

void	func_export(t_parse *cmds, t_env **env)
{
	char	*var_name;
	char	*var_value;
	char	*equals;
	char	*cmd_cpy;
	int		i;

	// char	**split_var;
	// char	*variable_join;
	if (!cmds->cmd_array[1])
	{
		export_without_args(env);
		return ;
	}
	i = 1;
	while (cmds->cmd_array[i])
	{
		cmd_cpy = ft_strdup(cmds->cmd_array[i]);
		equals = ft_strchr(cmd_cpy, '=');
		if (!equals)
			my_setenv(cmd_cpy, "", env);
		else
		{
			*equals = '\0';
			var_name = ft_strdup(cmds->cmd_array[i]);
			var_value = equals + 1;
			my_setenv(env_str, var_name, var_value, env);
			free(var_name);
			free(cmd_cpy);
		}
	}
	// split_var = ft_split(cmds->cmd_array[1], '=');
	// variable = split_var[0];
	// value = split_var[1];
	// variable_join = ft_strjoin(variable, "=");
	// if (check_variable(env, variable_join, value))
	// 	return ;
	// else
	// {
	// 	// if (variable[0] != '\0' && value[0] != '\0')
	// 	printf("HERE\n");
	// 	if (check_export_variable(variable[0]))
	// 		push_env_list(env, ft_strjoin(variable_join, value),
	// 			ft_strlen(ft_strjoin(variable_join, value)));
	// 	else
	// 		return ;
	// }
}
