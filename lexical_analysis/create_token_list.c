/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 12:07:50 by ftanon            #+#    #+#             */
/*   Updated: 2024/07/28 16:01:20 by ftanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	push_token_list(t_token **tok_list, char *str, t_env *env, t_data *data)
{
	t_token	*element;
	t_token	*last;

	last = *tok_list;
	element = malloc(sizeof(t_token));
	element->len = 0;
	element->j = 0;
	element->i = 0;
	get_len_pos(data, env, element);
	store_string(element, str, env, data);
	element->next = NULL;
	if (*tok_list == NULL)
	{
		*tok_list = element;
		return ;
	}
	while (last->next != NULL)
		last = last->next;
	last->next = element;
	element->prev = last;
}

// **** attention segfault
// tok_list = NULL;
void	create_token_list(t_data *data, t_token **tok_list, t_env *env_list)
{
	data->pos = 0;
	data->num_token = 0;
	while (data->input[data->pos] != '\0')
	{
		while (is_space(data->input[data->pos]))
			data->pos++;
		if (data->input[data->pos] == '\0')
			break ;
		push_token_list(tok_list, data->input + data->pos, env_list, data);
	}
}
