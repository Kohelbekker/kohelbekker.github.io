/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_elements2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperesad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 18:47:57 by aperesad          #+#    #+#             */
/*   Updated: 2019/03/07 18:47:59 by aperesad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

void		shape_center(t_sdl *sdl, t_shape *tmp, char **word)
{
	int		*vec;
	int		i;

	i = 0;
	if (row_nbr(word) != 3)
		error(sdl, "Wrong amount of arguments for center setting\n");
	vec = check_cycle(sdl, 0, 0, word);
	tmp->center = int_to_vec(vec, 10.0);
	free(vec);
}

void		shape_axis(t_sdl *sdl, t_shape *tmp, char **word)
{
	int		*vec;
	int		i;

	i = 0;
	if (row_nbr(word) != 3)
		error(sdl, "Wrong amount of arguments for axis setting\n");
	vec = check_cycle(sdl, 0, 0, word);
	tmp->axis_v = int_to_vec(vec, 1.0);
	tmp->axis_v = unit_vector(tmp->axis_v);
	free(vec);
}

void		shape_radius(t_sdl *sdl, t_shape *tmp, char **word)
{
	int		a;
	int		j;

	j = 0;
	if (row_nbr(word) != 1)
		error(sdl, "Wrong amount of arguments for radius setting\n");
	while (word[0][j])
	{
		if (word[0][0] == '-')
			error(sdl, "please, use only positive values for radius!\n");
		if (!(ft_isdigit(word[0][j])))
			error(sdl, "Error, non-digit values, please use only integers!\n");
		j++;
	}
	a = ft_atoi(word[0]);
	if (a < 1)
		error(sdl, "Please, use radius equal to 1 or bigger\n");
	tmp->radius = ((double)a / 10.0);
}
