/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 16:57:41 by rrichard          #+#    #+#             */
/*   Updated: 2024/07/31 17:03:37 by rrichard         ###   ########.fr       */
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

	environ = malloc(sizeof(char *) * (listlen(env_list) + 1));
	while (current)
	{
		*environ = current->env_var;
		environ++;
		current = current->next;
	}
	return (environ);
}
