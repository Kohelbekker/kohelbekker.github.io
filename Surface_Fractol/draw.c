/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperesad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 15:53:09 by aperesad          #+#    #+#             */
/*   Updated: 2018/10/02 15:53:15 by aperesad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void			my_pixel_put_to_image(t_fract *f, t_draw *d)
{
	int	color; 
	f->ind = d->n + 1 - (log(2) / 1.0) / log(2);
	f->r = (sin(f->k_ind1 * f->ind + f->c_ind) * f->byte_ind + f->byte_c);
	f->g = (sin(f->k_ind2 * f->ind + f->c_ind) * f->byte_ind + f->byte_c);
	f->b = (sin(f->k_ind3 * f->ind + f->c_ind) * f->byte_ind + f->byte_c);
	color = SDL_MapRGB(f->mlx->img->format, f->r, f->g, f->b);
	((int *)f->mlx->img->pixels)[d->y * WDTH + d->x] = color; 
}

void			my_pixel_put_to_image2(t_fract *f, t_draw *d)
{
	Uint32	color = 0xffffff;
	((int *)f->mlx->img->pixels)[d->y * WDTH + d->x] = color;
}

void			*draw(t_fract *p_f)
{
	t_draw		*d;
	t_fract		*f;

	f = p_f;
	d = (t_draw *)malloc(sizeof(t_draw));
	d->y = -1;
	while (++d->y < HGHT)
	{
		d->c_im = f->man->min_im + d->y * f->man->cur_im;
		d->x = 0;
		while (d->x < WDTH)
		{
			d->c_re = f->man->min_re + d->x * f->man->cur_re;
			d->z_re = d->c_re;
			d->z_im = d->c_im;
			d->z_sre = d->z_re * d->z_re;
			d->z_sim = d->z_im * d->z_im;
			fractals(f, d);
			//printf("ROW # %d\n", d->x);
			(d->z_sre + d->z_sim > 4.0) ? (my_pixel_put_to_image(
				f, d)) : (my_pixel_put_to_image2(f, d));
			d->x++;
		}
	}
	free(d);
	return (p_f);
}
