/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperesad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 19:07:33 by aperesad          #+#    #+#             */
/*   Updated: 2017/11/01 19:29:20 by aperesad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *arr1, const void *arr2, size_t n)
{
	unsigned char	*p;
	unsigned char	*p2;
	size_t			i;

	i = 0;
	p = (unsigned char*)arr1;
	p2 = (unsigned char*)arr2;
	while (i < n && p[i] == p2[i])
		i++;
	if (i == n)
		return (0);
	return (p[i] - p2[i]);
}
