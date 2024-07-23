/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 15:56:45 by ftanon            #+#    #+#             */
/*   Updated: 2024/07/23 15:54:02 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	search_command(t_parse *par_list, t_data *data)
{
	int		i;
	
	while (par_list)
	{
		i = 0;
		if (!par_list->cmd_array[0])
			break ;
		if (ft_strncmp(par_list->cmd_array[0], "/", 1) == 0)
			par_list->path = ft_strdup(par_list->cmd_array[0]);
		else if (is_builtin(par_list))
			par_list->builtin = 1;
		else
		{
			while (data->all_paths[i])
			{
				par_list->path = find_path(data->all_paths[i], par_list->cmd_array);
				if (par_list->path != NULL)
					break ;
				i++;
			}
		}
		par_list = par_list->next;
	}
}
