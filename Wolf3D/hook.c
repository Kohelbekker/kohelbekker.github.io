/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperesad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 20:09:50 by aperesad          #+#    #+#             */
/*   Updated: 2018/10/24 20:09:53 by aperesad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void		reload(t_wolf *w)
{
	mlx_destroy_image(w->mlx->mlx_p, w->mlx->img);
	init2(w);
}

int			movehook(t_wolf *w)
{
	if (w->hook->forw == 1)
		move_forward(w);
	if (w->hook->back == 1)
		move_back(w);
	if (w->hook->left == 1)
		turn_left(w);
	if (w->hook->right == 1)
		turn_right(w);
	draw(w);
	return (0);
}

int			hooks_released(int key, t_wolf *w)
{
	if (key == 36)
		reload(w);
	if (key == 257)
	{
		w->speed = MOVE;
		w->rotate = ROT;
	}
	if (key == 126)
		w->hook->forw = 0;
	if (key == 125)
		w->hook->back = 0;
	if (key == 124)
		w->hook->left = 0;
	if (key == 123)
		w->hook->right = 0;
	if (key == 49)
		w->flag = ((w->flag == 1) ? (0) : (1));
	return (0);
}

int			hooks_pressed(int key, t_wolf *w)
{
	if (key == 257)
	{
		w->speed = MOVE2;
		w->rotate = ROT2;
	}
	if (key == 126)
		w->hook->forw = 1;
	if (key == 125)
		w->hook->back = 1;
	if (key == 124)
		w->hook->left = 1;
	if (key == 123)
		w->hook->right = 1;
	if (key == 53)
	{
		mlx_clean(w->mlx);
		exit(0);
	}
	return (0);
}
