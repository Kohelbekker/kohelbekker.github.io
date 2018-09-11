/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperesad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 12:55:31 by aperesad          #+#    #+#             */
/*   Updated: 2017/11/06 12:55:32 by aperesad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	char	*p;
	char	*p2;
	size_t	i;

	p = (char *)dest;
	p2 = (char *)src;
	i = 0;
	while (i < n && p2[i] != '\0')
	{
		p[i] = p2[i];
		i++;
	}
	if (p2[i] == '\0')
	{
		while (i < n)
		{
			p[i] = '\0';
			i++;
		}
	}
	return (dest);
}
