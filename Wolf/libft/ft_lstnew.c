/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperesad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 13:35:24 by aperesad          #+#    #+#             */
/*   Updated: 2017/11/20 13:36:02 by aperesad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list *lstnew;

	lstnew = (t_list *)malloc(sizeof(*lstnew));
	if (lstnew == NULL)
		return (NULL);
	if (content == NULL)
	{
		lstnew->content = NULL;
		lstnew->content_size = 0;
		lstnew->next = NULL;
	}
	else
	{
		lstnew->content = (void *)malloc(content_size);
		if (lstnew->content == NULL)
		{
			return (NULL);
			free(lstnew);
		}
		lstnew->content = ft_memcpy(lstnew->content, content, content_size);
		lstnew->content_size = content_size;
		lstnew->next = NULL;
	}
	return (lstnew);
}
