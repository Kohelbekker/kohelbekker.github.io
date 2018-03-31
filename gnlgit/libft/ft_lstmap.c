/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperesad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 16:48:25 by aperesad          #+#    #+#             */
/*   Updated: 2017/11/21 16:49:32 by aperesad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *newlst;
	t_list *stor;
	t_list *head;

	if (lst == NULL || f == NULL)
		return (NULL);
	stor = (*f)(lst);
	newlst = ft_lstnew(stor->content, stor->content_size);
	if (newlst == NULL)
		return (NULL);
	head = newlst;
	lst = lst->next;
	while (lst != NULL)
	{
		stor = (*f)(lst);
		newlst->next = ft_lstnew(stor->content, stor->content_size);
		if (newlst->next == NULL)
			return (NULL);
		newlst = newlst->next;
		lst = lst->next;
	}
	return (head);
}
