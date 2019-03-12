/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperesad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 18:45:26 by aperesad          #+#    #+#             */
/*   Updated: 2019/03/07 18:45:28 by aperesad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

void		shape_angle(t_sdl *sdl, t_shape *tmp, char **word)
{
	int		a;
	int		j;

	j = 0;
	if (row_nbr(word) != 1)
		error(sdl, "Wrong amount of arguments for radius setting\n");
	while (word[0][j])
	{
		if (word[0][0] == '-')
			error(sdl, "please, use only positive values for angles!\n");
		if (!(ft_isdigit(word[0][j])))
			error(sdl, "Error, non-digit values, please use only integers!\n");
		j++;
	}
	a = ft_atoi(word[0]);
	if (a < 0 || a > 180)
		error(sdl, "Please, use valid amount of degrees for angle \
			(from 0 to 180)\n");
	tmp->angle = (double)a;
}

void		shape_color(t_sdl *sdl, t_shape *tmp, char **word)
{
	int		*vec;
	int		j;

	j = 0;
	if (row_nbr(word) != 3)
		error(sdl, "Wrong amount of arguments for center setting\n");
	vec = check_cycle(sdl, 0, 0, word);
	while (j < 3)
	{
		if (vec[j] > 255 || vec[j] < 0)
			error(sdl, "Please, use numbers between 0 and 255 to set color\n");
		j++;
	}
	tmp->color = int_to_vec(vec, 1.0);
	free(vec);
}

void		shape_specular(t_sdl *sdl, t_shape *tmp, char **word)
{
	int		a;
	int		j;

	j = 0;
	if (row_nbr(word) != 1)
		error(sdl, "Wrong amount of arguments for specular setting\n");
	while (word[0][j])
	{
		if (!(ft_isdigit(word[0][j])) && word[0][0] != '-')
			error(sdl, "Error, non-digit values, please use only integers!\n");
		j++;
	}
	a = ft_atoi(word[0]);
	if (a < -1 || a > 1000)
		error(sdl, "Please, use numbers between -1 and 1000 to set specular\n");
	tmp->specular = a;
}
