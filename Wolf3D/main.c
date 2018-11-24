/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperesad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 17:20:41 by aperesad          #+#    #+#             */
/*   Updated: 2018/10/24 20:09:16 by aperesad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void		draw(t_wolf *w)
{
	if (w->mlx->img != NULL)
	{
		mlx_destroy_image(w->mlx->mlx_p, w->mlx->img);
		w->mlx->img = mlx_new_image(w->mlx->mlx_p, WDTH, HGHT);
		w->mlx->data = mlx_get_data_addr(w->mlx->img, &w->mlx->bpp,
			&w->mlx->sl, &w->mlx->ed);
	}
	pre_draw(w);
	mlx_put_image_to_window(w->mlx->mlx_p, w->mlx->win_p, w->mlx->img, 0, 0);
}

void		init2(t_wolf *w)
{
	w->mlx->img = mlx_new_image(w->mlx->mlx_p, WDTH, HGHT);
	w->mlx->data = mlx_get_data_addr(w->mlx->img, &w->mlx->bpp,
		&w->mlx->sl, &w->mlx->ed);
	w->vect_x = -1;
	w->vect_y = 0;
	w->ang_x = 0;
	w->ang_y = 0.66;
	w->flag = 0;
	w->pers_dist = 0;
	w->hook->left = 0;
	w->hook->right = 0;
	w->hook->forw = 0;
	w->hook->back = 0;
	w->speed = MOVE;
	w->rotate = ROT;
	w->start_x = w->tmp_startx;
	w->start_y = w->tmp_starty;
}

void		init(t_wolf *w)
{
	if (!(w->mlx->mlx_p = mlx_init()) ||
		!(w->mlx->img = mlx_new_image(w->mlx->mlx_p, WDTH, HGHT)) ||
		!(w->mlx->data = mlx_get_data_addr(w->mlx->img, &w->mlx->bpp,
		&w->mlx->sl, &w->mlx->ed)) ||
		!(w->mlx->win_p = mlx_new_window(w->mlx->mlx_p, WDTH, HGHT,
			"Wolf3D - aperesad")))
		mlx_clean(w->mlx);
	create_texture(w);
	w->vect_x = -1;
	w->vect_y = 0;
	w->ang_x = 0;
	w->ang_y = 0.66;
	w->flag = 0;
	w->pers_dist = 0;
	w->hook->left = 0;
	w->hook->right = 0;
	w->hook->forw = 0;
	w->hook->back = 0;
	w->speed = MOVE;
	w->rotate = ROT;
}

int			main(int ac, char **av)
{
	t_wolf	*w;

	if (ac != 2)
		error("No map or more then one map!\nUsage: ./wolf3d [map]");
	if (!(w = (t_wolf *)malloc(sizeof(t_wolf))) ||
		!(w->mlx = (t_mlx *)malloc(sizeof(t_mlx))) ||
		!(w->map = (t_map *)malloc(sizeof(t_map))) ||
		!(w->hook = (t_hook *)malloc(sizeof(t_hook))))
		error("Malloc error");
	check_map(av[1], w);
	init(w);
	pre_draw(w);
	mlx_put_image_to_window(w->mlx->mlx_p, w->mlx->win_p, w->mlx->img, 0, 0);
	mlx_hook(w->mlx->win_p, 17, 0L, exit_x, 0);
	mlx_hook(w->mlx->win_p, 2, 1L << 0, hooks_pressed, w);
	mlx_hook(w->mlx->win_p, 3, 1L << 1, hooks_released, w);
	mlx_loop_hook(w->mlx->mlx_p, movehook, w);
	mlx_loop(w->mlx->mlx_p);
	return (0);
}
