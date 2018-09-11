/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperesad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/02 17:48:00 by aperesad          #+#    #+#             */
/*   Updated: 2018/07/02 17:48:02 by aperesad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void			ft_draw(t_mlx *mlx)
{
	int			x;
	int			y;
	t_points	a;
	t_points	b;

	y = 0;
	while (y < mlx->map->height)
	{
		x = 0;
		while (x < mlx->map->width)
		{
			a = mlx->map->points[y][x];
			b = mlx->map->points[y][x + 1];
			if (x + 1 < mlx->map->width)
				points(center(a, mlx), center(b, mlx), mlx);
			if (y + 1 < mlx->map->height)
				points(center(a, mlx), center(mlx->map->points[y + 1][x],
					mlx), mlx);
			x++;
		}
		y++;
	}
}

void			points(t_points a1, t_points a2, t_mlx *mlx)
{
	t_brez		b;

	b.dy = (int)ABS((int)a2.y - (int)a1.y);
	b.dx = (int)ABS((int)a2.x - (int)a1.x);
	b.sig_x = (int)a1.x > (int)a2.x ? -1 : 1;
	b.sig_y = (int)a1.y > (int)a2.y ? -1 : 1;
	b.err = (int)b.dx - (int)b.dy;
	while ((int)a1.x != (int)a2.x || (int)a1.y != (int)a2.y)
	{
		mlx_pixel_put(mlx->mlx_p, mlx->win_p, (int)a1.x, (int)a1.y, 0xffa500);
		b.err2 = (int)b.err * 2;
		if (b.err2 > -b.dx)
		{
			b.err -= (int)b.dy;
			a1.x += (int)b.sig_x;
		}
		if (b.err2 < b.dy)
		{
			b.err += (int)b.dx;
			a1.y += (int)b.sig_y;
		}
	}
}
