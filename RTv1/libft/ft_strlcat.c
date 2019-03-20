/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperesad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 12:55:05 by aperesad          #+#    #+#             */
/*   Updated: 2017/11/06 12:55:08 by aperesad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	int		j;
	size_t	lsrc;
	size_t	ldest;
	size_t	i;

	i = ft_strlen(dest);
	j = 0;
	lsrc = ft_strlen(src);
	ldest = ft_strlen(dest);
	if (size < ldest + 1)
		return (lsrc + size);
	if (size > ldest + 1)
	{
		while (i < size - 1)
		{
			dest[i] = src[j];
			i++;
			j++;
		}
		dest[i] = '\0';
	}
	return (ldest + lsrc);
}
