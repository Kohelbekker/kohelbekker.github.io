/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_center.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperesad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/02 17:59:28 by aperesad          #+#    #+#             */
/*   Updated: 2018/07/02 17:59:30 by aperesad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_points		scale_mat(t_points a, t_mlx *mlx)
{
	t_points	v;

	v.x = a.x;
	v.y = a.y;
	v.z = a.z;
	v.x *= mlx->map->scale;
	v.y *= mlx->map->scale;
	v.z *= mlx->map->scale;
	return (v);
}

t_points		angle_mat(t_points a, t_mlx *mlx)
{
	t_points	n_a;
	double		x;
	double		y;
	double		z;

	x = a.x;
	z = a.z;
	y = a.y;
	n_a.x = cos(mlx->map->cam_x) * x + sin(mlx->map->cam_y) * z;
	n_a.z = -sin(mlx->map->cam_y) * x + cos(mlx->map->cam_x) * z;
	z = n_a.z;
	n_a.y = cos(mlx->map->cam_x) * y - sin(mlx->map->cam_y) * z;
	n_a.z = sin(mlx->map->cam_y) * y + cos(mlx->map->cam_x) * z;
	n_a.color = a.color;
	return (n_a);
}

t_points		center(t_points a, t_mlx *mlx)
{
	a.z *= DIST_Z;
	a.x -= (double)((mlx->map->width - 1) / 2.0) * DIST;
	a.y -= (double)((mlx->map->height - 1) / 2.0) * DIST;
	a.z -= (double)((mlx->map->z_max + mlx->map->z_min) / 2.0);
	a = scale_mat(a, mlx);
	a.x += W_WID / 2.0;
	a.y += W_HGHT / 2.0;
	a = angle_mat(a, mlx);
	a.x = (int)a.x;
	a.y = (int)a.y;
	a.z = (int)a.z;
	return (a);
}
