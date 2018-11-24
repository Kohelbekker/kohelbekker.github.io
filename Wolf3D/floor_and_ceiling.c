/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_and_ceiling.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperesad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 20:09:38 by aperesad          #+#    #+#             */
/*   Updated: 2018/10/24 20:09:41 by aperesad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include <stdio.h>

void		my_pixel_put_to_image2(char *data, int x, int y, t_wolf *w)
{
	int		a;
	int		q;

	a = ((w->flag == 0) ? 4 : 10);
	q = w->tex_floor_y * w->tex[a].sl + w->tex_floor_x * w->tex[a].bpp;
	data[y * w->mlx->sl + x * w->mlx->bpp / 8] = w->tex[a].data[q];
	data[y * w->mlx->sl + x * w->mlx->bpp / 8 + 1] = w->tex[a].data[q + 1];
	data[y * w->mlx->sl + x * w->mlx->bpp / 8 + 2] = w->tex[a].data[q + 2];
}

void		my_pixel_put_to_image3(char *data, int x, int y, t_wolf *w)
{
	int		a;
	int		q;
	int		c;

	a = ((w->flag == 0) ? 5 : 11);
	c = (HGHT - y);
	q = w->tex_floor_y * w->tex[a].sl + w->tex_floor_x * w->tex[a].bpp;
	data[c * w->mlx->sl + x * w->mlx->bpp / 8] = w->tex[a].data[q];
	data[c * w->mlx->sl + x * w->mlx->bpp / 8 + 1] = w->tex[a].data[q + 1];
	data[c * w->mlx->sl + x * w->mlx->bpp / 8 + 2] = w->tex[a].data[q + 2];
}

void		wall_position(t_wolf *w)
{
	if (w->side == 0 && w->x_ray > 0)
	{
		w->floor_wall_x = w->x;
		w->floor_wall_y = w->y + w->x_wall;
	}
	else if (w->side == 0 && w->x_ray < 0)
	{
		w->floor_wall_x = w->x + 1.0;
		w->floor_wall_y = w->y + w->x_wall;
	}
	else if (w->side == 1 && w->y_ray < 0)
	{
		w->floor_wall_x = w->x + w->x_wall;
		w->floor_wall_y = w->y + 1.0;
	}
	else
	{
		w->floor_wall_x = w->x + w->x_wall;
		w->floor_wall_y = w->y;
	}
}

void		draw_floor_and_ceiling(t_wolf *w)
{
	int		j;

	wall_position(w);
	j = w->wall_end;
	while (j < HGHT)
	{
		w->tmp_dist = HGHT / (2.0 * j - HGHT);
		w->corr = (w->tmp_dist - w->pers_dist) / (w->ray_l - w->pers_dist);
		w->tmp_floor_x = w->corr * w->floor_wall_x +
		(1.0 - w->corr) * w->start_x;
		w->tmp_floor_y = w->corr * w->floor_wall_y +
		(1.0 - w->corr) * w->start_y;
		w->tex_floor_x = (int)(w->tmp_floor_x * TEX_W) % TEX_W;
		w->tex_floor_y = (int)(w->tmp_floor_y * TEX_H) % TEX_H;
		my_pixel_put_to_image2(w->mlx->data, w->i, j, w);
		my_pixel_put_to_image3(w->mlx->data, w->i, j, w);
		j++;
	}
}
