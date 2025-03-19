/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiagi <mbiagi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 12:18:44 by mbiagi            #+#    #+#             */
/*   Updated: 2025/01/29 10:39:43 by mbiagi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, int (*f)(int), void (*del)(int))
{
	t_list	*lf;
	t_list	*l;

	if (!lst)
		return (NULL);
	l = NULL;
	while (lst)
	{
		lf = ft_lstnew(f(lst->n));
		if (!lf)
			ft_lstdelone(lf, del);
		ft_lstadd_back(&l, lf);
		lst = lst->next;
	}
	return (l);
}
