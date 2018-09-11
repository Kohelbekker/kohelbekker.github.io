/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_rotate.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperesad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/02 18:05:24 by aperesad          #+#    #+#             */
/*   Updated: 2018/07/02 18:05:26 by aperesad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void			hook_rotate(int key, t_mlx *mlx)
{
	double		c_x;
	double		c_y;
	int			l;
	int			w;

	l = mlx->map->height - 1;
	w = mlx->map->width - 1;
	c_x = ((mlx->map->points[l][w].x + mlx->map->points[0][0].x) / 2.0);
	c_y = ((mlx->map->points[l][w].y + mlx->map->points[0][0].y) / 2.0);
	if (key == 83)
		make_rotate_ox(mlx, ((M_PI / 180) * 5), c_y);
	else if (key == 86)
		make_rotate_ox(mlx, ((-M_PI / 180) * 5), c_y);
	else if (key == 84)
		make_rotate_oy(mlx, ((M_PI / 180) * 5), c_x);
	else if (key == 87)
		make_rotate_oy(mlx, ((-M_PI / 180) * 5), c_x);
	else if (key == 85)
		make_rotate_oz(mlx, ((M_PI / 180) * 5), c_x, c_y);
	else if (key == 88)
		make_rotate_oz(mlx, ((-M_PI / 180) * 5), c_x, c_y);
}

void			make_rotate_ox(t_mlx *mlx, double ang, double b)
{
	int			j;
	int			i;
	double		r;
	double		s;

	j = 0;
	i = 0;
	while (i < mlx->map->height)
	{
		while (j < mlx->map->width)
		{
			r = mlx->map->points[i][j].y - b;
			s = mlx->map->points[i][j].z;
			mlx->map->points[i][j].y = (cos(ang) * r + s * (-sin(ang)));
			mlx->map->points[i][j].z = (r * sin(ang) + s * cos(ang));
			mlx->map->points[i][j].y += b;
			j++;
		}
		i++;
		j = 0;
	}
}

void			make_rotate_oy(t_mlx *mlx, double ang, double a)
{
	int			j;
	int			i;
	double		q;
	double		s;

	j = 0;
	i = 0;
	while (i < mlx->map->height)
	{
		while (j < mlx->map->width)
		{
			q = mlx->map->points[i][j].x - a;
			s = mlx->map->points[i][j].z;
			mlx->map->points[i][j].x = (cos(ang) * q + s * (sin(ang)));
			mlx->map->points[i][j].z = (q * (-sin(ang)) + s * cos(ang));
			mlx->map->points[i][j].x += a;
			j++;
		}
		i++;
		j = 0;
	}
}

void			make_rotate_oz(t_mlx *mlx, double ang, double a, double b)
{
	int			j;
	int			i;
	double		q;
	double		r;

	j = 0;
	i = 0;
	while (i < mlx->map->height)
	{
		while (j < mlx->map->width)
		{
			q = mlx->map->points[i][j].x - a;
			r = mlx->map->points[i][j].y - b;
			mlx->map->points[i][j].x = (cos(ang) * q + r * (-sin(ang)));
			mlx->map->points[i][j].y = (q * sin(ang) + r * cos(ang));
			mlx->map->points[i][j].x += a;
			mlx->map->points[i][j].y += b;
			j++;
		}
		i++;
		j = 0;
	}
}
