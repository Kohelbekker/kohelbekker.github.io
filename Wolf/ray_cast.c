/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperesad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 20:10:37 by aperesad          #+#    #+#             */
/*   Updated: 2018/10/24 20:10:39 by aperesad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void		my_pixel_put_to_image(char *data, int x, int y, t_wolf *w)
{
	int a;

	a = ((w->flag == 0) ? w->n_t : (w->n_t + 6));
	data[y * w->mlx->sl + x * w->mlx->bpp / 8] = w->tex[a].data
	[w->y_t * w->tex[a].sl + w->x_t * w->tex[a].bpp];
	data[y * w->mlx->sl + x * w->mlx->bpp / 8 + 1] = w->tex[a].data
	[w->y_t * w->tex[a].sl + w->x_t * w->tex[a].bpp + 1];
	data[y * w->mlx->sl + x * w->mlx->bpp / 8 + 2] = w->tex[a].data
	[w->y_t * w->tex[a].sl + w->x_t * w->tex[a].bpp + 2];
}

void		ray_step(t_wolf *w)
{
	if (w->x_ray < 0)
	{
		w->step_x = -1;
		w->l_ox = (w->start_x - w->x) * w->delt_x;
	}
	else
	{
		w->step_x = 1;
		w->l_ox = (w->x + 1.0 - w->start_x) * w->delt_x;
	}
	if (w->y_ray < 0)
	{
		w->step_y = -1;
		w->l_oy = (w->start_y - w->y) * w->delt_y;
	}
	else
	{
		w->step_y = 1;
		w->l_oy = (w->y + 1.0 - w->start_y) * w->delt_y;
	}
}

void		ray_length(t_wolf *w)
{
	while (w->wall == 0)
	{
		if (w->l_ox < w->l_oy)
		{
			w->l_ox += w->delt_x;
			w->x += w->step_x;
			w->side = 0;
		}
		else
		{
			w->l_oy += w->delt_y;
			w->y += w->step_y;
			w->side = 1;
		}
		if (w->map->map[w->x][w->y] > 0)
			w->wall = 1;
	}
	w->ray_l = ((w->side == 0) ? ((w->x - w->start_x + (1 - w->step_x) / 2) /
		w->x_ray) : ((w->y - w->start_y + (1 - w->step_y) / 2) / w->y_ray));
	w->line_h = ((double)HGHT / w->ray_l);
	w->wall_start = -w->line_h / 2.0 + (double)HGHT / 2.0;
	w->wall_end = w->line_h / 2.0 + (double)HGHT / 2.0;
	w->wall_start = (w->wall_start < 0) ? (0) : (w->wall_start);
	w->wall_end = (w->wall_end >= HGHT) ? (HGHT - 1) : (w->wall_end);
}

void		texture_xy(t_wolf *w)
{
	w->x_wall = ((w->side == 0) ? (w->start_y + w->ray_l * w->y_ray)
			: (w->x_wall = w->start_x + w->ray_l * w->x_ray));
	w->x_wall -= ((w->x_wall >= 0) ? ((int)w->x_wall) : ((int)w->x_wall - 1));
	w->x_t = (int)(w->x_wall * (double)(TEX_W));
	if (w->side == 0 && w->x_ray > 0)
		w->x_t = TEX_W - w->x_t - 1;
	if (w->side == 1 && w->y_ray < 0)
		w->x_t = TEX_W - w->x_t - 1;
}

void		pre_draw(t_wolf *w)
{
	w->i = 0;
	while (w->i < WDTH)
	{
		w->camx = 2.0 * w->i / (double)WDTH - 1;
		w->x_ray = w->vect_x + w->ang_x * w->camx;
		w->y_ray = w->vect_y + w->ang_y * w->camx;
		w->x = (int)w->start_x;
		w->y = (int)w->start_y;
		w->delt_x = fabs(1.0 / w->x_ray);
		w->delt_y = fabs(1.0 / w->y_ray);
		w->wall = 0;
		ray_step(w);
		ray_length(w);
		texture_xy(w);
		texture_type(w);
		while (w->wall_start < w->wall_end)
		{
			w->tmp = w->wall_start * 256 - HGHT * 128 + w->line_h * 128;
			w->y_t = ((w->tmp * TEX_W) / w->line_h) / 256;
			my_pixel_put_to_image(w->mlx->data, w->i, w->wall_start, w);
			w->wall_start++;
		}
		draw_floor_and_ceiling(w);
		w->i++;
	}
}
