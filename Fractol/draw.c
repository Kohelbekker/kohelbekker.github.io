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

void			my_pixel_put_to_image(char *data, t_fract *f, t_draw *d)
{
	f->ind = d->n + 1 - (log(2) / 1.0) / log(2);
	f->r = (sin(f->k_ind1 * f->ind + f->c_ind) * f->byte_ind + f->byte_c);
	f->g = (sin(f->k_ind2 * f->ind + f->c_ind) * f->byte_ind + f->byte_c);
	f->b = (sin(f->k_ind3 * f->ind + f->c_ind) * f->byte_ind + f->byte_c);
	data[d->y * f->mlx->sl + d->x * f->mlx->bpp / 8] = f->r;
	data[d->y * f->mlx->sl + d->x * f->mlx->bpp / 8 + 1] = f->g;
	data[d->y * f->mlx->sl + d->x * f->mlx->bpp / 8 + 2] = f->b;
}

void			my_pixel_put_to_image2(char *data, t_fract *f, int x, int y)
{
	f->mlx->color = 0xffffff;
	data[y * f->mlx->sl + x * f->mlx->bpp / 8] = f->mlx->color;
	data[y * f->mlx->sl + x * f->mlx->bpp / 8 + 1] = f->mlx->color >> 8;
	data[y * f->mlx->sl + x * f->mlx->bpp / 8 + 2] = f->mlx->color >> 16;
}

void			my_threads(t_fract *f)
{
	t_fract		p_f[100];
	pthread_t	p[100];
	int			status;
	int			i;

	i = -1;
	while (++i < 100)
	{
		p_f[i] = *f;
		p_f[i].start = i * (WDTH / 100);
		p_f[i].end = (i + 1) * (WDTH / 100);
	}
	i = -1;
	while (++i < 100)
	{
		if ((status = pthread_create(&p[i], NULL, draw, &p_f[i])) != 0)
			error1(f, "error, can't create thread");
	}
	while (i-- >= 0)
		pthread_join(p[i], NULL);
}

void			*draw(void *p_f)
{
	t_draw		*d;
	t_fract		*f;

	f = (t_fract *)p_f;
	d = (t_draw *)malloc(sizeof(t_draw));
	d->y = -1;
	while (++d->y < HGHT)
	{
		d->c_im = f->man->min_im + d->y * f->man->cur_im;
		d->x = f->start;
		while (d->x < f->end)
		{
			d->c_re = f->man->min_re + d->x * f->man->cur_re;
			d->z_re = d->c_re;
			d->z_im = d->c_im;
			d->z_sre = d->z_re * d->z_re;
			d->z_sim = d->z_im * d->z_im;
			fractals(f, d);
			(d->z_sre + d->z_sim > 4.0) ? (my_pixel_put_to_image(f->mlx->data,
				f, d)) : (my_pixel_put_to_image2(f->mlx->data, f, d->x, d->y));
			d->x++;
		}
	}
	free(d);
	return (p_f);
}
