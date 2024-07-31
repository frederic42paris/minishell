/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 13:10:27 by rrichard          #+#    #+#             */
/*   Updated: 2024/01/09 18:12:27 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

// Takes as a parameter an element and frees the memory of the element’s
void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!(lst) || !(del))
		return ;
	(*del)(lst->content);
	free(lst);
}
