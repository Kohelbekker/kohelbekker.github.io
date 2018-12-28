/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zoom.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperesad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 15:52:53 by aperesad          #+#    #+#             */
/*   Updated: 2018/10/02 15:53:01 by aperesad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		scale(t_fract *f)
{
	f->k = 1.0 / f->zoom;
	f->man->min_re = f->re + (f->man->min_re - f->re) * f->k;
	f->man->min_im = f->im + (f->man->min_im - f->im) * f->k;
	f->man->max_re = f->re + (f->man->max_re - f->re) * f->k;
	f->man->max_im = f->im + (f->man->max_im - f->im) * f->k;
	f->man->cur_re = (f->man->max_re - f->man->min_re) / (WDTH - 1);
	f->man->cur_im = (f->man->max_im - f->man->min_im) / (HGHT - 1);
}

int			zoom_hook(t_fract *f)
{
	int		x;
	int		y;
	int		a;

	x = f->mlx->mlx_p.motion.x;
	y = f->mlx->mlx_p.motion.y;
	a = f->mlx->mlx_p.button.button;
	f->re = (double)x / ((double)WDTH / (f->man->max_re - f->man->min_re))
	+ f->man->min_re;
	f->im = (double)y / ((double)HGHT / (f->man->max_im - f->man->min_im))
	+ f->man->min_im;
	f->zoom = 1.0;
	if ((a == SDL_BUTTON_LEFT || a == SDL_BUTTON_X1))
	{
		f->zoom = 1.25;
		f->man->max_iter++;
		f->man->start++;
		scale(f);
	}
	if ((a == SDL_BUTTON_RIGHT || a == SDL_BUTTON_X2) && f->man->start > -4)
	{
		f->zoom = 1.0 / 1.25;
		f->man->max_iter--;
		f->man->start--;
		scale(f);
	}
	draw(f);
	return (0);
}
