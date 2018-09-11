/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperesad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 19:43:47 by aperesad          #+#    #+#             */
/*   Updated: 2017/11/06 19:43:51 by aperesad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *dest, const char *str)
{
	int i;
	int j;

	i = 0;
	j = ft_strlen(dest);
	while (str[i] != '\0')
	{
		dest[j++] = str[i++];
	}
	dest[j] = '\0';
	return (dest);
}
