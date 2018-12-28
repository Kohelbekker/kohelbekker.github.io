/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperesad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 15:11:45 by aperesad          #+#    #+#             */
/*   Updated: 2017/11/01 16:13:19 by aperesad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*p1;
	char	*p2;
	size_t	i;

	if (dest == NULL && src == NULL)
		return (NULL);
	i = -1;
	p1 = (char *)dest;
	p2 = (char *)src;
	if (p1 > p2)
	{
		while ((int)n > 0)
		{
			*(p1 + n - 1) = *(p2 + n - 1);
			n--;
		}
	}
	else
	{
		while (++i < n)
			*(p1 + i) = *(p2 + i);
	}
	return (dest);
}
