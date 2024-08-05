/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 19:11:15 by sumseo            #+#    #+#             */
/*   Updated: 2024/08/05 11:29:35 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	delete_one_env(t_env **env_list, char *name)
{
	t_env	*temp;

	temp = *env_list;
	while (temp)
	{
		if (!ft_strncmp(temp->env_var, name, ft_strlen(name))
			&& (temp->env_var[ft_strlen(name)] == '='))
			break ;
		temp = temp->next;
	}
	if (!temp)
		return ;
	if (*env_list == temp)
		*env_list = temp->next;
	if (temp->next)
		temp->next->prev = temp->prev;
	if (temp->prev)
		temp->prev->next = temp->next;
	free(temp->env_var);
	free(temp);
}

int	func_unset(t_parse *cmds, t_env **env_list)
{
	int		i;

	i = 1;
	if (!cmds->cmd_array[i])
		return ((void)printf("unset: not enough arguments\n"), 1);
	while (cmds->cmd_array[i])
	{
		delete_one_env(env_list, cmds->cmd_array[i]);
		i++;
	}
	return (0);
}
