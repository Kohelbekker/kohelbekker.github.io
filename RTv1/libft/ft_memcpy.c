/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperesad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/31 18:30:49 by aperesad          #+#    #+#             */
/*   Updated: 2017/10/31 18:30:59 by aperesad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	*p;
	char	*p1;

	if (dest == NULL && src == NULL)
		return (NULL);
	i = 0;
	p = dest;
	p1 = (char *)src;
	while (i < n)
	{
		p[i] = p1[i];
		i++;
	}
	return (dest);
}
