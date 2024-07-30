/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_env_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 18:10:02 by ftanon            #+#    #+#             */
/*   Updated: 2024/07/30 15:19:42 by ftanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	push_env_list(t_env **env_list, const char *str)
{
	t_env	*element;
	t_env	*last;

	last = *env_list;
	element = malloc(sizeof(t_env));
	element->env_var = ft_strdup(str);
	element->next = NULL;
	if (*env_list == NULL)
	{
		*env_list = element;
		return ;
	}
	while (last->next != NULL)
		last = last->next;
	last->next = element;
	element->prev = last;
}

void	store_env_list(char **envp, t_env **env_list)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		push_env_list(env_list, envp[i]);
		i++;
	}
}

void	display_env_list(t_env *env_list)
{
	while (env_list)
	{
		printf("%s\n", env_list->env_var);
		env_list = env_list->next;
	}
}
