/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperesad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 12:55:40 by aperesad          #+#    #+#             */
/*   Updated: 2017/11/06 12:55:41 by aperesad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int ch)
{
	int	j;

	j = (int)ft_strlen(str);
	while (j != 0 && str[j] != (char)ch)
		j--;
	if (str[j] == ch)
		return ((char*)str + j);
	return (NULL);
}
