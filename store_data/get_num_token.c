/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_num_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 15:37:32 by ftanon            #+#    #+#             */
/*   Updated: 2024/07/28 15:38:29 by ftanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	get_num_token(t_token *tok_list, t_data *data)
{
	int	i;

	i = 0;
	while (tok_list)
	{
		i++;
		tok_list = tok_list->next;
	}
	data->num_token = i;
}
