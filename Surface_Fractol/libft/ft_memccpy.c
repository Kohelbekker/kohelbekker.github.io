/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperesad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/31 20:02:45 by aperesad          #+#    #+#             */
/*   Updated: 2017/11/01 17:41:08 by aperesad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	unsigned char	*p;
	unsigned char	*p2;
	size_t			i;

	if (dest == NULL && src == NULL)
		return (NULL);
	i = 0;
	p = (unsigned char *)dest;
	p2 = (unsigned char *)src;
	while (i < n)
	{
		p[i] = p2[i];
		if (p2[i] == (unsigned char)c)
			return (dest + i + 1);
		i++;
	}
	return (NULL);
}
