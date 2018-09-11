/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_translation_scale.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperesad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/02 17:48:47 by aperesad          #+#    #+#             */
/*   Updated: 2018/07/02 17:48:49 by aperesad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void			hook_translate(int key, t_mlx *mlx)
{
	if (key == 126)
		make_traslation(-8, mlx, 'Y');
	else if (key == 125)
		make_traslation(8, mlx, 'Y');
	else if (key == 123)
		make_traslation(-8, mlx, 'X');
	else if (key == 124)
		make_traslation(8, mlx, 'X');
}

void			hook_scale(int key, t_mlx *mlx)
{
	if (key == 78)
		make_scale(mlx, key);
	else if (key == 69)
		make_scale(mlx, key);
}

void			make_traslation(int a, t_mlx *mlx, char c)
{
	int			ox;
	int			oy;
	int			j;
	int			i;

	i = 0;
	ox = ((c == 'X') ? a : 0);
	oy = ((c == 'Y') ? a : 0);
	while (i < mlx->map->height)
	{
		j = 0;
		while (j < mlx->map->width)
		{
			mlx->map->points[i][j].x += ox;
			mlx->map->points[i][j].y += oy;
			j++;
		}
		i++;
	}
}

void			make_scale(t_mlx *mlx, int key)
{
	double		i;

	i = 1.2;
	if (key == 69)
		mlx->map->scale *= i;
	else
	{
		if (mlx->map->scale > 0.2)
			mlx->map->scale /= i;
	}
}
