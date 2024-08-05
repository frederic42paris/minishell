/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 16:01:57 by ftanon            #+#    #+#             */
/*   Updated: 2024/08/05 11:13:37 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	store_str(t_token *tok_list, t_redir *element)
{
	if (tok_list->operator[0] == '<')
		element->type = 0;
	else if (tok_list->operator[0] == '>')
		element->type = 1;
	element->token = ft_shield_strdup(tok_list->operator);
	tok_list = tok_list->next;
	element->name = ft_shield_strdup(tok_list->word);
	return (0);
}

void	init_redir(t_redir	*element)
{
	element->type = 0;
	element->name = NULL;
	element->token = NULL;
	element->exist = 0;
	element->access = 0;
	element->next = NULL;
}

int	push_redirection(t_redir **redir_list, t_token *tok_list)
{
	t_redir	*element;
	t_redir	*last;

	last = *redir_list;
	element = malloc(sizeof(t_redir));
	if (element == NULL)
		return (1);
	init_redir(element);
	if (store_str(tok_list, element))
		return (1);
	if (*redir_list == NULL)
	{
		*redir_list = element;
		element->prev = NULL;
		return (0);
	}
	while (last->next != NULL)
		last = last->next;
	last->next = element;
	element->prev = last;
	return (0);
}

int	split_redirection(t_token *tok_list, t_parse *par_list)
{
	while (tok_list)
	{
		if (tok_list->operator && tok_list->operator[0] == '|')
			break ;
		if (tok_list->operator)
		{
			if (push_redirection(&par_list->redirection, tok_list))
				return (1);
			if (tok_list->operator[0] == '<')
				par_list->infile_nb++;
			else if (tok_list->operator[0] == '>')
				par_list->outfile_nb++;
			tok_list = tok_list->next;
			tok_list = tok_list->next;
		}
		else
			tok_list = tok_list->next;
	}
	return (0);
}

int	store_redirection(t_token *tok_list, t_parse *par_list)
{
	int	i;
	int	k;

	while (par_list)
	{
		i = 0;
		k = 0;
		i = count_words_pipe(tok_list);
		if (split_redirection(tok_list, par_list))
			return (1);
		while (k < i)
		{
			tok_list = tok_list->next;
			k++;
		}
		if (tok_list && tok_list->operator && tok_list->operator[0] == '|')
			tok_list = tok_list->next;
		par_list = par_list->next;
	}
	return (0);
}
