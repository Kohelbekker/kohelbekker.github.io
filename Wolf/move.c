/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperesad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 20:10:21 by aperesad          #+#    #+#             */
/*   Updated: 2018/10/24 20:10:29 by aperesad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void		move_forward(t_wolf *w)
{
	if (!(w->map->map[(int)(w->start_x + w->vect_x * w->speed + 0.15)]
		[(int)(w->start_y + 0.15)]) &&
		!(w->map->map[(int)(w->start_x + w->vect_x * w->speed - 0.15)]
		[(int)(w->start_y - 0.15)]) &&
		!(w->map->map[(int)(w->start_x + w->vect_x * w->speed - 0.15)]
		[(int)(w->start_y + 0.15)]) &&
		!(w->map->map[(int)(w->start_x + w->vect_x * w->speed + 0.15)]
		[(int)(w->start_y - 0.15)]))
		w->start_x += w->vect_x * w->speed;
	if (!(w->map->map[(int)(w->start_x + 0.15)]
		[(int)(w->start_y + w->vect_y * w->speed + 0.15)]) &&
		!(w->map->map[(int)(w->start_x - 0.15)]
		[(int)(w->start_y + w->vect_y * w->speed - 0.15)]) &&
		!(w->map->map[(int)(w->start_x + 0.15)]
		[(int)(w->start_y + w->vect_y * w->speed - 0.15)]) &&
		!(w->map->map[(int)(w->start_x - 0.15)]
		[(int)(w->start_y + w->vect_y * w->speed + 0.15)]))
		w->start_y += w->vect_y * w->speed;
}

void		move_back(t_wolf *w)
{
	if (!(w->map->map[(int)(w->start_x - w->vect_x * w->speed + 0.15)]
		[(int)(w->start_y + 0.15)]) &&
		!(w->map->map[(int)(w->start_x - w->vect_x * w->speed - 0.15)]
		[(int)(w->start_y + 0.15)]) &&
		!(w->map->map[(int)(w->start_x - w->vect_x * w->speed - 0.15)]
		[(int)(w->start_y - 0.15)]) &&
		!(w->map->map[(int)(w->start_x - w->vect_x * w->speed + 0.15)]
		[(int)(w->start_y - 0.15)]))
		w->start_x -= w->vect_x * w->speed;
	if (!(w->map->map[(int)(w->start_x + 0.15)]
		[(int)(w->start_y - w->vect_y * w->speed + 0.15)]) &&
		!(w->map->map[(int)(w->start_x - 0.15)]
		[(int)(w->start_y - w->vect_y * w->speed - 0.15)]) &&
		!(w->map->map[(int)(w->start_x + 0.15)]
		[(int)(w->start_y - w->vect_y * w->speed - 0.15)]) &&
		!(w->map->map[(int)(w->start_x - 0.15)]
		[(int)(w->start_y - w->vect_y * w->speed + 0.15)]))
		w->start_y -= w->vect_y * w->speed;
}

void		turn_left(t_wolf *w)
{
	w->oldvect_x = w->vect_x;
	w->vect_x = w->vect_x * cos(-w->rotate) - w->vect_y * sin(-w->rotate);
	w->vect_y = w->oldvect_x * sin(-w->rotate) + w->vect_y * cos(-w->rotate);
	w->oldang_x = w->ang_x;
	w->ang_x = w->ang_x * cos(-w->rotate) - w->ang_y * sin(-w->rotate);
	w->ang_y = w->oldang_x * sin(-w->rotate) + w->ang_y * cos(-w->rotate);
}

void		turn_right(t_wolf *w)
{
	w->oldvect_x = w->vect_x;
	w->vect_x = w->vect_x * cos(w->rotate) - w->vect_y * sin(w->rotate);
	w->vect_y = w->oldvect_x * sin(w->rotate) + w->vect_y * cos(w->rotate);
	w->oldang_x = w->ang_x;
	w->ang_x = w->ang_x * cos(w->rotate) - w->ang_y * sin(w->rotate);
	w->ang_y = w->oldang_x * sin(w->rotate) + w->ang_y * cos(w->rotate);
}
