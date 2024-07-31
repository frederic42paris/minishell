/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrichard <rrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 14:47:49 by rrichard          #+#    #+#             */
/*   Updated: 2024/01/09 18:12:53 by rrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

// Allocates and returns a new element. The variable ’content’ is initialized
t_list	*ft_lstnew(void *content)
{
	t_list	*ptr;

	ptr = malloc(sizeof(t_list));
	if (!ptr)
		return (NULL);
	ptr->content = content;
	ptr->next = NULL;
	return (ptr);
}
