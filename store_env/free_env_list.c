/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_env_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 13:33:41 by ftanon            #+#    #+#             */
/*   Updated: 2024/07/28 11:25:03 by ftanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_env_list(t_env	**env_list)
{
	t_env	*nextnode;

	while (*env_list)
	{
		nextnode = (*env_list)->next;
		free((*env_list)->env_var);
		free(*env_list);
		(*env_list) = nextnode;
	}
}
