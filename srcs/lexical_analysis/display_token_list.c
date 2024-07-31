/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_token_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 15:34:55 by ftanon            #+#    #+#             */
/*   Updated: 2024/07/28 15:36:05 by ftanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	display_token_list(t_token *tok_list)
{
	printf("--------------------\n");
	while (tok_list)
	{
		if (tok_list->word)
			printf("[%s]\n", tok_list->word);
		if (tok_list->operator)
			printf("%s\n", tok_list->operator);
		tok_list = tok_list->next;
	}
	printf("--------------------\n");
}
