/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 17:24:11 by rrichard          #+#    #+#             */
/*   Updated: 2024/07/31 15:42:02 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_exec(int (**fd)[2], pid_t **pid, char *str)
{
	free(*fd);
	free(*pid);
	if (str)
		perror(str);
	return ;
}
