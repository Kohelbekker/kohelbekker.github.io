/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperesad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 19:07:08 by aperesad          #+#    #+#             */
/*   Updated: 2017/11/16 19:07:11 by aperesad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	unsigned long int	nb;
	int					i;
	int					sign;

	i = 0;
	sign = 1;
	nb = 0;
	while (SPACE(str[i]) || SPACEB(str[i]))
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] != '\0' && ft_isdigit(str[i]))
	{
		nb = nb + (int)(str[i] - '0');
		i++;
		if (str[i] != '\0' && ft_isdigit(str[i]))
			nb = nb * 10;
	}
	if (nb >= 9223372036854775807 && sign == 1)
		return (-1);
	if (nb > 9223372036854775807 && sign == -1)
		return (0);
	return (sign * nb);
}
