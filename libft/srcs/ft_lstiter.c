/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 13:20:53 by rrichard          #+#    #+#             */
/*   Updated: 2024/01/09 18:12:53 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

// Iterates the list ’lst’ and applies the function ’f’ to the content of each
void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	**tmp;

	if (!(lst) || !(f))
		return ;
	while (lst)
	{
		tmp = &lst->next;
		(*f)(lst->content);
		lst = *tmp;
	}
}
