/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 16:01:57 by ftanon            #+#    #+#             */
/*   Updated: 2024/07/24 11:33:40 by ftanon           ###   ########.fr       */
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

void	push_redirection(t_redir **redir_list, t_token *tok_list)
{
	t_redir	*element;
	t_redir	*last;
	int		len;

	last = *redir_list;
	element = malloc(sizeof(t_redir));
	element->type = 0;
	element->name = NULL;
	element->token = NULL;
	element->exist = 0;
	element->access = 0;
	element->next = NULL;

	if (tok_list->operator[0] == '<')
		element->type = 0;
	else if (tok_list->operator[0] == '>')
		element->type = 1;
	len = ft_strlen(tok_list->operator);
	element->token = (char *)malloc(sizeof(char) * (len + 1));
	ft_strlcpy(element->token, tok_list->operator, len + 1);
	tok_list = tok_list->next;
	len = ft_strlen(tok_list->word);
	element->name = (char *)malloc(sizeof(char) * (len + 1));
	ft_strlcpy(element->name, tok_list->word, len + 1);

	if (*redir_list == NULL)
	{
		*redir_list = element;
		element->prev = NULL;
		return ;
	}
	while (last->next != NULL)
		last = last->next;
	last->next = element;
	element->prev = last;
}

void	split_redirection(t_token *tok_list, t_parse *par_list)
{
	while (tok_list)
	{
		if (tok_list->operator && tok_list->operator[0] == '|')
			break ;
		if (tok_list->operator)
		{
			push_redirection(&par_list->redirection, tok_list);
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

void	store_redirection(t_token *tok_list, t_parse *par_list)
{
	int	i;
	int	k;

	while (par_list)
	{
		i = 0;
		k = 0;
		i = count_words_pipe_redirect(tok_list);
		split_redirection(tok_list, par_list);
		while (k < i)
		{
			tok_list = tok_list->next;
			k++;
		}
		if (tok_list && tok_list->operator && tok_list->operator[0] == '|')
			tok_list = tok_list->next;
		par_list = par_list->next;
	}
}
