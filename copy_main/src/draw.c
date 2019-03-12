/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperesad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 18:25:17 by aperesad          #+#    #+#             */
/*   Updated: 2019/03/07 18:25:18 by aperesad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

t_vector		check_colors(t_vector col)
{
	col[0] = MIN(255, MAX(0, (int)col[0]));
	col[1] = MIN(255, MAX(0, (int)col[1]));
	col[2] = MIN(255, MAX(0, (int)col[2]));
	return (col);
}

int				draw(t_sdl *sdl, double u, double v, int sdl_color)
{
	int			j;
	t_vector	col;
	int			i;

	i = -WDTH / 2;
	while (i < WDTH / 2)
	{
		j = -HGHT / 2;
		while (j < HGHT / 2)
		{
			u = i * sdl->x_unit;
			v = j * sdl->y_unit;
			sdl->ray->b = (t_vector){u, v, sdl->projection_plane_z};
			sdl->ray->b = unit_vector(rot(sdl->ray->b, sdl));
			col = trace_ray(sdl, sdl->ray, 1, MAX_I);
			col = check_colors(col);
			sdl_color = SDL_MapRGB(sdl->surf->format, col[0], col[1], col[2]);
			((int *)sdl->surf->pixels)[(HGHT / 2 - j - 1) * WDTH +
				(WDTH / 2 + i)] = sdl_color;
			j++;
		}
		i++;
	}
	return (0);
}
