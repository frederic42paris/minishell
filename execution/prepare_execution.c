/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 16:57:41 by rrichard          #+#    #+#             */
/*   Updated: 2024/07/31 17:14:35 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	listlen(t_env *env_list)
{
	int	i;

	i = 0;
	while (env_list)
	{
		i++;
		env_list = env_list->next;
	}
	return (i);
}

char	**transform_envlist(t_env *env_list)
{
	t_env	*current;
	char	**environ;
	int		i;

	current = env_list;
	i = 0;
	environ = malloc(sizeof(char *) * (listlen(env_list) + 1));
	while (current)
	{
		environ[i] = current->env_var;
		i++;
		current = current->next;
	}
	environ[i] = NULL;
	return (environ);
}
