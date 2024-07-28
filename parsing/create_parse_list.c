/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_parse_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 11:43:11 by ftanon            #+#    #+#             */
/*   Updated: 2024/07/28 15:23:49 by ftanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	push_parse_list(t_parse **par_list)
{
	t_parse	*element;
	t_parse	*last;

	last = *par_list;
	element = malloc(sizeof(t_parse));
	element->redirection = NULL;
	element->infile_nb = 0;
	element->outfile_nb = 0;
	element->path = NULL;
	element->builtin = 0;
	element->next = NULL;
	element->cmd_array = (char **)ft_calloc(2, sizeof(char *));
	element->cmd_array[0] = (char *)ft_calloc (1, sizeof(char));
	if (*par_list == NULL)
	{
		*par_list = element;
		element->prev = NULL;
		return ;
	}
	while (last->next != NULL)
		last = last->next;
	last->next = element;
	element->prev = last;
}

void	create_parse_list(t_token *tok_list, t_parse **par_list)
{
	int	i;
	int	k;

	while (tok_list)
	{
		i = 0;
		k = 0;
		i = count_words_pipe(tok_list);
		push_parse_list(par_list);
		while (k < i)
		{
			tok_list = tok_list->next;
			k++;
		}
		if (tok_list && tok_list->operator && tok_list->operator[0] == '|')
			tok_list = tok_list->next;
	}
}
