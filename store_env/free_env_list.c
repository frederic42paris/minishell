/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_env_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 13:33:41 by ftanon            #+#    #+#             */
/*   Updated: 2024/07/31 16:26:01 by rrichard         ###   ########.fr       */
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
