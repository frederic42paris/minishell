/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 16:01:57 by ftanon            #+#    #+#             */
/*   Updated: 2024/07/31 15:42:02 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_words_operator_redirect(t_token *tok_list)
{
	int	len;

	len = 0;
	while (tok_list)
	{
		if (tok_list->operator && (tok_list->operator[0] == '|'
				|| tok_list->operator[0] == '>'
				|| tok_list->operator[0] == '<'))
			break ;
		len++;
		tok_list = tok_list->next;
	}
	return (len);
}

int	count_words_pipe_redirect(t_token *tok_list)
{
	int	len;

	len = 0;
	while (tok_list)
	{
		if (tok_list->operator && tok_list->operator[0] == '|')
			break ;
		len++;
		tok_list = tok_list->next;
	}
	return (len);
}

t_redir	*push_redirection(t_redir *redir_list, t_token *tok_list)
{
	t_redir	*element;
	t_redir	*last;

	element = malloc(sizeof(t_redir));
	ft_memset(element, 0, sizeof(t_redir));
	if (tok_list->operator[0] == '<')
		element->type = 0;
	else if (tok_list->operator[0] == '>')
		element->type = 1;
	element->token = ft_strdup(tok_list->operator);
	tok_list = tok_list->next;
	if (tok_list)
		element->name = ft_strdup(tok_list->word);
	if (redir_list == NULL)
	{
		element->prev = NULL;
		return (element);
	}
	last = redir_list;
	while (last->next != NULL)
		last = last->next;
	last->next = element;
	element->prev = last;
	return (redir_list);
}

void	split_redirection(t_token *tok_list, t_parse *par_list)
{
	while (tok_list)
	{
		if (tok_list->operator && tok_list->operator[0] == '|')
			break ;
		if (tok_list->operator)
		{
			par_list->redirection = push_redirection(par_list->redirection, tok_list);
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
}

void	store_redirection(t_token *tok_list, t_parse **par_list)
{
	int	i;
	int	k;
	t_parse	*current;

	current = *par_list;
	while (current)
	{
		i = 0;
		k = 0;
		i = count_words_pipe_redirect(tok_list);
		split_redirection(tok_list, current);
		while (k < i)
		{
			tok_list = tok_list->next;
			k++;
		}
		if (tok_list && tok_list->operator && tok_list->operator[0] == '|')
			tok_list = tok_list->next;
		current = current->next;
	}
}
