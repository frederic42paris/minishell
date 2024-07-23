/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 15:40:18 by ftanon            #+#    #+#             */
/*   Updated: 2024/07/22 16:37:28 by ftanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// void	free_redirection(t_token	**tok_list)
// {
// 	t_token	*nextnode;
// 	t_token	*prevnode;

// 	while ((*tok_list)->next)
// 	{
// 		if ((*tok_list)->operator && (*tok_list)->operator[0] == '<')
// 		{
// 			nextnode = (*tok_list)->next;
// 			prevnode = (*tok_list)->prev;
// 			free((*tok_list)->operator);
// 			free((*tok_list)->word);
// 			free(*tok_list);
// 			(*tok_list) = nextnode;
// 			(*tok_list)->prev = prevnode;

// 			prevnode = (*tok_list)->prev;
// 			free((*tok_list)->operator);
// 			free((*tok_list)->word);
// 			free(*tok_list);
// 			(*tok_list) = prevnode;

// 			// nextnode = (*tok_list)->next;
// 			// free((*tok_list)->operator);
// 			// free((*tok_list)->word);
// 			// free(*tok_list);
// 			// (*tok_list) = nextnode;
// 		}
// 		else
// 			*tok_list = (*tok_list)->next;
// 	}
	

// 	// if (*par_list == NULL)
// 	// {
// 	// 	*par_list = element;
// 	// 	element->prev = NULL;
// 	// 	return ;
// 	// }
// 	// while (last->next != NULL)
// 	// 	last = last->next;
// 	// last->next = element;
// 	// element->prev = last;
// 	// nextnode = (*tok_list)->next;
// 	// free((*tok_list)->operator);
// 	// free((*tok_list)->word);
// 	// free(*tok_list);
// 	// (*tok_list) = nextnode;

// 	// nextnode = (*tok_list)->next;
// 	// free((*tok_list)->operator);
// 	// free((*tok_list)->word);
// 	// free(*tok_list);
// 	// (*tok_list) = nextnode;
	
// 	// t_token	*nextnode;

// 	// while (*tok_list)
// 	// {
// 	// 	if ((*tok_list)->operator && (*tok_list)->operator[0] == '<')
// 	// 	{
// 	// 		nextnode = (*tok_list)->next;
// 	// 		free((*tok_list)->operator);
// 	// 		free((*tok_list)->word);
// 	// 		free(*tok_list);
// 	// 		(*tok_list) = nextnode;
// 	// 		nextnode = (*tok_list)->next;
// 	// 		free((*tok_list)->operator);
// 	// 		free((*tok_list)->word);
// 	// 		free(*tok_list);
// 	// 		(*tok_list) = nextnode;
// 	// 	}
// 	// }
// }