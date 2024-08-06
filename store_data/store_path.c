/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 15:41:01 by ftanon            #+#    #+#             */
/*   Updated: 2024/08/06 13:33:30 by ftanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	store_path(t_env *env_list, t_data *data)
{
	if (data->all_paths)
	{
		free_array(data->all_paths);
		data->all_paths = NULL;
	}
	while (env_list)
	{
		if (ft_strncmp(env_list->env_var, "PATH", 4) == 0)
		{
			data->all_paths = ft_split(env_list->env_var + 5, ':');
			if (data->all_paths == NULL)
			{
				perror("Malloc error");
				exit(EXIT_FAILURE);
			}
			break ;
		}
		env_list = env_list->next;
	}
	return (0);
}
