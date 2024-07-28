/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 15:56:45 by ftanon            #+#    #+#             */
/*   Updated: 2024/07/28 12:53:35 by ftanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_builtin_function(char *str)
{
	size_t	len;

	len = ft_strlen(str);
	if (
		(len == ft_strlen("echo") && ft_strncmp(str, "echo", len) == 0)
		|| (len == ft_strlen("cd") && ft_strncmp(str, "cd", len) == 0)
		|| (len == ft_strlen("pwd") && ft_strncmp(str, "pwd", len) == 0)
		|| (len == ft_strlen("export") && ft_strncmp(str, "export", len) == 0)
		|| (len == ft_strlen("unset") && ft_strncmp(str, "unset", len) == 0)
		|| (len == ft_strlen("env") && ft_strncmp(str, "env", len) == 0)
		|| (len == ft_strlen("exit") && ft_strncmp(str, "exit", len) == 0)
	)
		return (1);
	else
		return (0);
}

char	*find_path(char *single_path, char **command)
{
	char	*joined;
	char	*path;

	joined = ft_strjoin(single_path, "/");
	path = ft_strjoin(joined, command[0]);
	if (access(path, R_OK) == 0)
	{
		free(joined);
		return (path);
	}
	free(joined);
	free(path);
	return (NULL);
}

void	compare_path(t_parse *par_list, t_data *data)
{
	int		i;

	i = 0;
	while (data->all_paths[i])
	{
		par_list->path = find_path(data->all_paths[i], par_list->cmd_array);
		if (par_list->path != NULL)
			break ;
		i++;
	}
}

void	search_command(t_parse *par_list, t_data *data)
{
	while (par_list)
	{
		if (!par_list->cmd_array[0])
			break ;
		if (ft_strncmp(par_list->cmd_array[0], "/", 1) == 0)
			par_list->path = ft_strdup(par_list->cmd_array[0]);
		else if (is_builtin_function(par_list->cmd_array[0]))
			par_list->builtin = 1;
		else
			compare_path(par_list, data);
		par_list = par_list->next;
	}
}
