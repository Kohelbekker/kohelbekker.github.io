/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperesad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 20:08:31 by aperesad          #+#    #+#             */
/*   Updated: 2017/11/13 20:08:33 by aperesad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strnequ(char const *s1, char const *s2, size_t n)
{
	int a;

	if (s1 == NULL || s2 == NULL)
		return (0);
	a = ft_strncmp(s1, s2, n);
	if (a == 0)
		return (1);
	return (0);
}
