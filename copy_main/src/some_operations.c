/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   some_operations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperesad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 18:39:11 by aperesad          #+#    #+#             */
/*   Updated: 2019/03/07 18:39:15 by aperesad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

int				*check_cycle(t_sdl *sdl, int j, int a, char **word)
{
	int			*vec;

	vec = (int *)malloc(sizeof(int) * 3);
	while (j < 3)
	{
		while (word[j][a])
		{
			if (!(ft_isdigit(word[j][a])) && word[j][0] != '-')
				error(sdl, "Error, non-digit values, please use only int!\n");
			a++;
		}
		vec[j] = ft_atoi(word[j]);
		j++;
		a = 0;
	}
	return (vec);
}

int				last_char(char *str)
{
	int			i;

	i = 0;
	while (str[i])
		i++;
	i--;
	return (i);
}

int				row_nbr(char **str)
{
	int			i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

t_vector		int_to_vec(int *a, double div)
{
	t_vector	vec;

	vec[0] = ((double)a[0]) / div;
	vec[1] = ((double)a[1]) / div;
	vec[2] = ((double)a[2]) / div;
	return (vec);
}

t_vector		v_div(double b, t_vector a)
{
	t_vector	tmp;

	tmp = (t_vector){b, b, b};
	return (a / tmp);
}
