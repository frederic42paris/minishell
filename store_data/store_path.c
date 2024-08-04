/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 15:41:01 by ftanon            #+#    #+#             */
/*   Updated: 2024/08/04 14:08:38 by ftanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	display_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		printf("%s\n", array[i++]);
}

int	store_path(t_env *env_list, t_data *data)
{
	while (env_list)
	{
		if (ft_strncmp(env_list->env_var, "PATH", 4) == 0)
		{
			if (data->all_paths)
				free_array(data->all_paths);
			data->all_paths = ft_split(env_list->env_var + 5, ':');
			if (data->all_paths == NULL)
				return (1);
			break ;
		}
		env_list = env_list->next;
	}
	return (0);
}

void	display_path(t_data *data)
{
	display_array(data->all_paths);
	printf("nb pipes : %d\n", data->has_pipe);
}
