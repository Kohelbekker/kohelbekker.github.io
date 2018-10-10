/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperesad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 17:20:41 by aperesad          #+#    #+#             */
/*   Updated: 2018/10/08 17:20:44 by aperesad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

#define rotSpeed ((M_PI / 180) * 10)
#define moveSpeed ((M_PI / 180) * 12)

int worldMap[24][24]=
{
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

int			error(char *str)
{
	ft_putendl(str);
	exit(1);
	return (0);
}

void			my_pixel_put_to_image(char *data, int x, int y, int color, t_mlx *mlx)
{
	data[y * mlx->sl + x * mlx->bpp / 8] = color;
	data[y * mlx->sl + x * mlx->bpp / 8 + 1] = color >> 8;
	data[y * mlx->sl + x * mlx->bpp / 8 + 2] = color >> 16;
}

int			exit_x(void)
{
	exit(1);
	return (0);
}

t_mlx		*mlx_clean(t_mlx *mlx)
{
	if (mlx->win_p != NULL)
		mlx_destroy_window(mlx->mlx_p, mlx->win_p);
	if (mlx->img != NULL)
		mlx_destroy_image(mlx->mlx_p, mlx->img);
	free(mlx);
	return (0);
}


void	pre_draw(t_wolf *w)
{
	w->count = 0;
	while (w->count < WDTH)
	{
		w->cam_OX = 2.0 * w->count / (double)WDTH - 1;
		w->x_ray = w->vect_X + w->planeX * w->cam_OX;
		w->y_ray = w->vect_Y + w->planeY * w->cam_OX;
		w->x = (int)w->posX;
		w->y = (int)w->posY;
		w->deltaOX = fabs(1.0 / w->x_ray);
		w->deltaOY = fabs(1.0 / w->y_ray);
		w->hit = 0;
		if (w->x_ray < 0)
		{
			w->stepX = -1;
			w->OXdist = (w->posX - w->x) * w->deltaOX;
		}
		else
		{
			w->stepX = 1;
			w->OXdist = (w->x + 1.0 - w->posX) * w->deltaOX;
		}
		if (w->y_ray < 0)
		{
			w->stepY = -1;
			w->OYdist = (w->posY - w->y) * w->deltaOY;
		}
		else
		{
			w->stepY = 1;
			w->OYdist = (w->y + 1.0 - w->posY) * w->deltaOY;
		}
		while (w->hit == 0)
		{
			if (w->OXdist < w->OYdist)
			{
				w->OXdist += w->deltaOX;
				w->x += w->stepX;
				w->side = 0;
			}
			else
			{
				w->OYdist += w->deltaOY;
				w->y += w->stepY;
				w->side = 1;
			}
			if (worldMap[w->x][w->y] > 0)
			w->hit = 1;
		}
		if (w->side == 0)
			w->wallDist = (w->x - w->posX + (1 - w->stepX) / 2) / w->x_ray;
		else
			w->wallDist = (w->y - w->posY + (1 - w->stepY) / 2) / w->y_ray;

		w->line_h = (int)((double)HGHT / w->wallDist);
		w->wall_start = -w->line_h / 2.0 + (double)HGHT / 2.0;
		if (w->wall_start < 0)
			w->wall_start = 0;
		w->wall_end = w->line_h / 2.0 +  (double)HGHT / 2.0;
		if (w->wall_end >= HGHT)
			w->wall_end = HGHT - 1;
		if (worldMap[w->x][w->y] == 1)
			w->mlx->color = 0xff0000;
		else if (worldMap[w->x][w->y] == 2)
			w->mlx->color = 0x178c05;
		else if (worldMap[w->x][w->y] == 3)
			w->mlx->color = 0x0055ff;
		else if (worldMap[w->x][w->y] == 4)
			w->mlx->color = 0xffffff;
		else
			w->mlx->color = 0xffff00;
		if (w->side == 1)
			w->mlx->color /= 2;
		while (w->wall_start <= w->wall_end)
		{	
			my_pixel_put_to_image(w->mlx->data, w->count, w->wall_start, w->mlx->color, w->mlx);
			w->wall_start++;
		}
		w->count++;
	}
}

int			hooks(int key, t_wolf *w)
{
	if (key == 53)
	{
		mlx_clean(w->mlx);
		exit(0);
	}
	if (key == 126)
    {
      if(!(worldMap[(int)(w->posX + w->vect_X * moveSpeed)][(int)w->posY]))
      	w->posX += w->vect_X * moveSpeed;
      if(!(worldMap[(int)w->posX][(int)(w->posY + w->vect_Y * moveSpeed)]))
      	w->posY += w->vect_Y * moveSpeed;
    }
    if (key == 125)
    {
      if(!(worldMap[(int)(w->posX - w->vect_X * moveSpeed)][(int)w->posY]))
      	w->posX -= w->vect_X * moveSpeed;
      if(!(worldMap[(int)w->posX][(int)(w->posY - w->vect_Y * moveSpeed)]))
      	w->posY -= w->vect_Y * moveSpeed;
    }
    if (key == 124)
    {
    	double oldvect_X = w->vect_X;
    	w->vect_X = w->vect_X * cos(-rotSpeed) - w->vect_Y * sin(-rotSpeed);
    	w->vect_Y = oldvect_X * sin(-rotSpeed) + w->vect_Y * cos(-rotSpeed);
    	double oldPlaneX = w->planeX;
    	w->planeX = w->planeX * cos(-rotSpeed) - w->planeY * sin(-rotSpeed);
    	w->planeY = oldPlaneX * sin(-rotSpeed) + w->planeY * cos(-rotSpeed);
    }
    if (key == 123)
    {
      double oldvect_X = w->vect_X;
      w->vect_X = w->vect_X * cos(rotSpeed) - w->vect_Y * sin(rotSpeed);
      w->vect_Y = oldvect_X * sin(rotSpeed) + w->vect_Y * cos(rotSpeed);
      double oldPlaneX = w->planeX;
      w->planeX = w->planeX * cos(rotSpeed) - w->planeY * sin(rotSpeed);
      w->planeY = oldPlaneX * sin(rotSpeed) + w->planeY * cos(rotSpeed);
    }
    mlx_destroy_image(w->mlx->mlx_p, w->mlx->img);
    w->mlx->img = mlx_new_image(w->mlx->mlx_p, WDTH, HGHT);
    w->mlx->data = mlx_get_data_addr(w->mlx->img, &w->mlx->bpp, &w->mlx->sl, &w->mlx->ed);
    pre_draw(w);
	mlx_put_image_to_window(w->mlx->mlx_p, w->mlx->win_p, w->mlx->img, 0, 0);
	return (0);
}

void		init(t_wolf *w)
{
	if (!(w->mlx->mlx_p = mlx_init()) ||
		!(w->mlx->img = mlx_new_image(w->mlx->mlx_p, WDTH, HGHT)) ||
		!(w->mlx->data = mlx_get_data_addr(w->mlx->img, &w->mlx->bpp,
		&w->mlx->sl, &w->mlx->ed)) ||
		!(w->mlx->win_p = mlx_new_window(w->mlx->mlx_p, WDTH, HGHT, "Wolf3D - aperesad")))
		mlx_clean(w->mlx);
	/////
	w->posX = 22;
	w->posY = 12;
	w->vect_X = -1;
	w->vect_Y = 0;
	w->planeX = 0;
	w->planeY = 0.66;
	/////
}

int		main(int ac, char **av)
{
	t_wolf	*w;

	if (ac != 2)
		error("No map!\nUsage: ./wolf3d [map]")
	if (!(w = (t_wolf *)malloc(sizeof(t_wolf))) ||
		!(w->mlx = (t_mlx *)malloc(sizeof(t_mlx))))
		error("Malloc error\n");
	init(w);

	pre_draw(w);

	mlx_put_image_to_window(w->mlx->mlx_p, w->mlx->win_p, w->mlx->img, 0, 0);
	mlx_hook(w->mlx->win_p, 2, 5, hooks, w);
	mlx_hook(w->mlx->win_p, 17, 1L << 17, exit_x, 0);
	mlx_loop(w->mlx->mlx_p);
	return (0);
}