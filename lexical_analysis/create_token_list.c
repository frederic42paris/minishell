/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 12:07:50 by ftanon            #+#    #+#             */
/*   Updated: 2024/08/05 11:25:35 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	push_token_list(t_token **tok_list, char *str, t_env *env, t_data *data)
{
	t_token	*element;
	t_token	*last;

	last = *tok_list;
	element = malloc(sizeof(t_token));
	if (element == NULL)
	{
		perror("Malloc error");
		exit(EXIT_FAILURE);
	}
	ft_bzero(element, sizeof(t_token));
	get_len_pos(data, env, element);
	if (store_string(element, str, env, data))
		return (1);
	element->next = NULL;
	if (*tok_list == NULL)
	{
		*tok_list = element;
		return (0);
	}
	while (last->next != NULL)
		last = last->next;
	last->next = element;
	element->prev = last;
	return (0);
}

// **** attention segfault
// tok_list = NULL;
int	create_token_list(t_data *data, t_token **tok_list, t_env *env_list)
{
	data->pos = 0;
	data->num_token = 0;
	while (data->input[data->pos] != '\0')
	{
		while (is_space(data->input[data->pos]))
			data->pos++;
		if (data->input[data->pos] == '\0')
			break ;
		if (push_token_list(tok_list, data->input + data->pos, env_list, data))
			return (1);
	}
	return (0);
}
