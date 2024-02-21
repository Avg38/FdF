/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avialle- <avialle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 15:08:55 by avialle-          #+#    #+#             */
/*   Updated: 2024/02/21 15:29:09 by avialle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	ft_lstadd_back_fdf(t_point **lst, t_point *new)
{
	t_point	*tmp;

	tmp = ft_lstlast_fdf(*lst);
	if (tmp == NULL)
		*lst = new;
	else
		tmp->next = new;
}

t_point	*ft_lstlast(t_point *lst)
{
	t_point	*tmp;

	tmp = lst;
	if (tmp == NULL)
		return (0);
	while (tmp->next != NULL)
		tmp = tmp->next;
	return (tmp);
}

t_point	*ft_lstnew(void *content)
{
	t_point	*elem;

	elem = malloc(sizeof(t_point));
	if (elem == NULL)
		return (NULL);
	elem->content = content;
	elem->next = NULL;
	return (elem);
}

