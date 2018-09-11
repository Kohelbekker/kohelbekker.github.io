/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperesad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/02 18:01:27 by aperesad          #+#    #+#             */
/*   Updated: 2018/07/02 18:01:29 by aperesad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void			zero_position(int key, t_mlx *mlx)
{
	int			i;
	int			j;

	i = 0;
	j = 0;
	if (key == 49)
	{
		while (i < mlx->map->height)
		{
			while (j < mlx->map->width)
			{
				mlx->map->points[i][j].x = j * DIST;
				mlx->map->points[i][j].y = i * DIST;
				mlx->map->points[i][j].z = mlx->map->points[i][j].h;
				j++;
			}
			j = 0;
			i++;
		}
		mlx->map->cam_x = 0.0;
		mlx->map->cam_y = 0.0;
		scale(mlx->map);
	}
}

int				hook_pointsonly(int key, t_mlx *mlx)
{
	if (key == 65)
	{
		mlx_clear_window(mlx->mlx_p, mlx->win_p);
		make_pointsonly(mlx);
	}
	return (0);
}

void			make_pointsonly(t_mlx *mlx)
{
	int			j;
	int			i;
	t_points	a;

	j = 0;
	i = 0;
	mlx_clear_window(mlx->mlx_p, mlx->win_p);
	mlx_string_put(mlx->mlx_p, mlx->win_p, 10, 10, 0xbd59ed, " FDF project. \
		Author: aperesad");
	while (i < mlx->map->height)
	{
		while (j < mlx->map->width)
		{
			a = center(mlx->map->points[i][j], mlx);
			mlx_pixel_put(mlx->mlx_p, mlx->win_p, (int)a.x, (int)a.y, 0x2fe502);
			j++;
		}
		j = 0;
		i++;
	}
}

int				hooks(int key, t_mlx *mlx)
{
	if (key == 53)
	{
		clean_mlx(mlx);
		exit(0);
	}
	hook_rotate(key, mlx);
	hook_translate(key, mlx);
	hook_scale(key, mlx);
	mlx_clear_window(mlx->mlx_p, mlx->win_p);
	zero_position(key, mlx);
	ft_draw(mlx);
	mlx_string_put(mlx->mlx_p, mlx->win_p, 10, 10, 0xbd59ed, " FDF project. \
		Author: aperesad");
	return (0);
}
