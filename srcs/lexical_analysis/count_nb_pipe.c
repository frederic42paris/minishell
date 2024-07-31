/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_nb_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 15:43:16 by ftanon            #+#    #+#             */
<<<<<<<< HEAD:srcs/lexical_analysis/count_nb_pipe.c
/*   Updated: 2024/07/17 18:54:29 by rrichard         ###   ########.fr       */
========
/*   Updated: 2024/07/28 16:08:02 by ftanon           ###   ########.fr       */
>>>>>>>> 16939a04bd97ccc16f423952e771f611d521774d:store_data/count_nb_pipe.c
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	count_nb_pipe(t_token *tok_list, t_data *data)
{
	int	nb;

	data->has_pipe = 0;
	nb = 0;
	while (tok_list)
	{
		if (tok_list->operator && tok_list->operator[0] == '|')
			nb++;
		tok_list = tok_list->next;
	}
	data->has_pipe = nb;
}
