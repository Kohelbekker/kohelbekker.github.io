/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperesad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 12:55:18 by aperesad          #+#    #+#             */
/*   Updated: 2017/11/06 12:55:19 by aperesad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *dest, const char *str, size_t n)
{
	size_t	i;
	int		j;

	i = 0;
	j = (int)ft_strlen(dest);
	while (i < n && str[i] != '\0')
		dest[j++] = str[i++];
	dest[j] = '\0';
	return (dest);
}
