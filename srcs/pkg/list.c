/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseniak <nseniak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 16:20:01 by nseniak           #+#    #+#             */
/*   Updated: 2023/01/05 17:28:51 by nseniak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	__lstdelone(t_list *lst, void (*del)(void *))
{
	if (del == NULL || lst == NULL)
		return ;
	del(lst->value);
	free(lst);
}

void	__lstclear(t_list **lst, void (*del)(void *))
{
	t_list *ptr;

	if (lst == NULL)
		return ;
	while (*lst != NULL)
	{
		ptr = (*lst)->next;
		__lstdelone(*lst, del);
		*lst = ptr;
	}
	*lst = NULL;
}
