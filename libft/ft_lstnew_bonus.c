/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiagi <mbiagi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 08:53:51 by mbiagi            #+#    #+#             */
/*   Updated: 2025/01/29 10:34:40 by mbiagi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(int content)
{
	t_list	*lst;

	lst = (t_list *)malloc(sizeof(t_list));
	if (!lst)
		return (NULL);
	lst -> n = content;
	lst -> next = NULL;
	return (lst);
}
/* 
int main()
{
	t_list *lst;

	lst = ft_lstnew("ciao");
	printf("content: %s, next: %s\n", (char *)lst->content, (char *)lst->next);
} */