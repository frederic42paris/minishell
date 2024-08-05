/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_parse_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 11:43:11 by ftanon            #+#    #+#             */
/*   Updated: 2024/08/05 10:42:54 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	init_to_zero(t_parse	*element)
{
	element->redirection = NULL;
	element->infile_nb = 0;
	element->outfile_nb = 0;
	element->path = NULL;
	element->environ = NULL;
	element->builtin = 0;
	element->cmd_array = (char **)ft_calloc(2, sizeof(char *));
	if (element->cmd_array == NULL)
	{
		perror("Malloc error");
		exit(EXIT_FAILURE);
	}
	element->cmd_array[0] = (char *)ft_calloc (1, sizeof(char));
	if (element->cmd_array[0] == NULL)
	{
		perror("Malloc error");
		exit(EXIT_FAILURE);
	}
	element->next = NULL;
	return (0);
}

int	push_parse_list(t_parse **par_list)
{
	t_parse	*element;
	t_parse	*last;

	last = *par_list;
	element = malloc(sizeof(t_parse));
	if (element == NULL)
	{
		perror("Malloc error");
		exit(EXIT_FAILURE);
	}
	if (init_to_zero(element))
		return (1);
	if (*par_list == NULL)
	{
		*par_list = element;
		element->prev = NULL;
		return (0);
	}
	while (last->next != NULL)
		last = last->next;
	last->next = element;
	element->prev = last;
	return (0);
}

int	create_parse_list(t_token *tok_list, t_parse **par_list)
{
	int	i;
	int	k;

	while (tok_list)
	{
		i = 0;
		k = 0;
		i = count_words_pipe(tok_list);
		if (push_parse_list(par_list))
			return (1);
		while (k < i)
		{
			tok_list = tok_list->next;
			k++;
		}
		if (tok_list && tok_list->operator && tok_list->operator[0] == '|')
			tok_list = tok_list->next;
	}
	return (0);
}
