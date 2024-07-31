/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/07/31 16:24:15 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

int	cmp(const void *a, const void *b)
{
	const char **ia = (const char **)a;
	const char **ib = (const char **)b;
	return (ft_strcmp(*ia, *ib));
}

void	export_without_args(char **environ)
{
	int		i;
	int		count;
	char	**sorted_environ;

	i = 0;
	count = 0;
	while (environ[count] != NULL)
		count++;
	sorted_environ = malloc(sizeof(char *) * (count + 1));
	while (i < count)
	{
		sorted_environ[i] = environ[i];
		i++;
	}
	sorted_environ[count] = NULL;
	qsort(sorted_environ, count, sizeof(char *), cmp);
	i = 0;
	while (environ[i] != NULL)
	{
		printf("declare -x \"%s\"\n", environ[i]);
		i++;
	}
	free(sorted_environ);
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

char	*find_env_var(char *name, char ***environ)
{
	char	**env;

	env = *environ;
	while (*env)
	{
		if (!ft_strncmp(*env, name, ft_strlen(name))
			&& *env[ft_strlen(name)] == '=')
			return (*env);
		env++;
	}
	return (NULL);
}

char	**create_env(char *env_str, char **environ)
{
	int 	count;
	int		i;
	char	**new_env;

	count = 0;
	i = 0;
	while (environ[count] != NULL)
		count++;
	new_env = malloc(sizeof(char *) * (count + 2));
	while (i < count)
	{
		new_env[i] = environ[i];
		i++;
	}
	new_env[i] = ft_strdup(env_str);
	new_env[i + 1] = NULL;
	return (new_env);
}

void	ft_setenv(char *env_str, char *name, char ***environ)
{
	char	*existing_env;

	existing_env = find_env_var(name, environ);
	if (existing_env)
		update_existing_env(env_str, name, environ);
	else
		*environ = create_env(env_str, *environ);
}


int	func_export(t_parse *cmds, char ***environ)
{
	char	*var_name;
	char	*equals;
	char	*cmd_cpy;
	int		i;

	i = 1;
	if (!cmds->cmd_array[i])
		export_without_args(*environ);
	else
	{
		while (cmds->cmd_array[i])
		{
			// if (!check_export_variable(cmds->cmd_array[i]))
			// 	return ;
			cmd_cpy = ft_strdup(cmds->cmd_array[i]);
			equals = ft_strchr(cmd_cpy, '=');
			if (!equals)
			{
				if (!find_env_var(cmd_cpy, environ))
					*environ = create_env(cmd_cpy, *environ);
			}
			else
			{
				*equals = '\0';
				var_name = ft_strdup(cmd_cpy);
				ft_setenv(cmds->cmd_array[i], var_name, environ);
				free(var_name);
				//free(equals + 1);
			}
			free(cmd_cpy);
			i++;
		}
	}
	return (0);
}
