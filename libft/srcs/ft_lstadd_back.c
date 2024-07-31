/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 13:13:24 by rrichard          #+#    #+#             */
/*   Updated: 2024/01/09 18:11:26 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

// Adds the element ’new’ at the end of the list.
void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (!(lst))
		return ;
	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	last = ft_lstlast(*lst);
	last->next = new;
}
