/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_env_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 18:10:02 by ftanon            #+#    #+#             */
/*   Updated: 2024/07/31 21:00:32 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	push_env_list(t_env **env_list, const char *str)
{
	t_env	*element;
	t_env	*last;

	last = *env_list;
	element = malloc(sizeof(t_env));
	if (element == NULL)
		return (1);
	element->env_var = ft_strdup(str);
	if (element->env_var == NULL)
		return (1);
	element->next = NULL;
	if (*env_list == NULL)
	{
		*env_list = element;
		return (0);
	}
	while (last->next != NULL)
		last = last->next;
	last->next = element;
	element->prev = last;
	return (0);
}

int	store_env_list(char **envp, t_env **env_list)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (push_env_list(env_list, envp[i]))
			return (1);
		i++;
	}
	return (0);
}

// void	display_env_list(t_env *env_list)
// {
// 	while (env_list)
// 	{
// 		printf("%s\n", env_list->env_var);
// 		env_list = env_list->next;
// 	}
// }
