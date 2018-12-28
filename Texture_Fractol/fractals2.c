/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperesad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 15:51:48 by aperesad          #+#    #+#             */
/*   Updated: 2018/10/02 15:51:52 by aperesad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	buffalo(t_fract *f, t_draw *d)
{
	d->n = 0;
	while (d->z_sre + d->z_sim <= 4.0 && d->n < f->man->max_iter)
	{
		d->z_im = fabsl(d->z_re * d->z_im) * -2.0;
		d->z_im += d->c_im;
		d->z_re = fabsl(d->z_sre - d->z_sim) + d->c_re;
		d->z_sre = d->z_re * d->z_re;
		d->z_sim = d->z_im * d->z_im;
		d->n++;
	}
}

void	burn(t_fract *f, t_draw *d)
{
	d->n = 0;
	while (d->z_sre + d->z_sim <= 4.0 && d->n < f->man->max_iter)
	{
		d->z_im = fabsl(pow(d->z_im + d->z_re, 2) - d->z_sre - d->z_sim);
		d->z_im += d->c_im;
		d->z_re = fabsl(d->z_sre - d->z_sim + d->c_re);
		d->z_sre = d->z_re * d->z_re;
		d->z_sim = d->z_im * d->z_im;
		d->n++;
	}
}

void	julia(t_fract *f, t_draw *d)
{
	d->n = 0;
	while (d->z_sre + d->z_sim <= 4.0 && d->n < f->man->max_iter)
	{
		d->z_im = pow(d->z_im + d->z_re, 2) - d->z_sre - d->z_sim;
		d->z_im += f->man->jul_ci;
		d->z_re = d->z_sre - d->z_sim + f->man->jul_cr;
		d->z_sre = d->z_re * d->z_re;
		d->z_sim = d->z_im * d->z_im;
		d->n++;
	}
}
