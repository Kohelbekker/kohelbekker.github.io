#include "fractol.h"

t_draw		*init_draw()
{
	t_draw	*d;

	if (!(d = (t_draw *)malloc(sizeof(t_draw))))
		return NULL;

	d->c_im = 0;
	d->c_re = 0;
	d->z_re = 0;
	d->z_im = 0;
	d->z_sim = 0;
	d->z_sre = 0;
	d->n = 0;
	d->x = 0;
	d->y = 0;
	return (d);
}

void		mandelbrot(t_fract *f, t_draw *d)
{
	
	while (d->z_sre + d->z_sim <= 4.0 && d->n < f->man->max_iter)
	{
		d->z_im = pow(d->z_im + d->z_re, 2) - d->z_sre - d->z_sim;
		d->z_im += d->c_im;
		d->z_re = d->z_sre - d->z_sim + d->c_re;
		d->z_sre = d->z_re * d->z_re;
		d->z_sim = d->z_im * d->z_im;
		d->n++;
	}
}

void		heart(t_fract *f, t_draw *d)
{
	while (d->z_sre + d->z_sim <= 4.0 && d->n < f->man->max_iter)
	{
		d->z_im = fabs(d->z_re) * d->z_im * 2.0;
		d->z_im += d->c_im;
		d->z_re = d->z_sre - d->z_sim + d->c_re;
		d->z_sre = d->z_re * d->z_re;
		d->z_sim = d->z_im * d->z_im;
		d->n++;
	}
}


void	tricorn(t_fract *f, t_draw *d)
{
	while (d->z_sre + d->z_sim <= 4.0 && d->n < f->man->max_iter)
	{
		d->z_im = d->z_re * d->z_im * -2.0;
		d->z_im += d->c_im;
		d->z_re = d->z_sre - d->z_sim + d->c_re;
		d->z_sre = d->z_re * d->z_re;
		d->z_sim = d->z_im * d->z_im;
		d->n++;
	}
}


void		buffalo(t_fract	*f, t_draw *d)
{
	while (d->z_sre + d->z_sim <= 4.0 && d->n < f->man->max_iter)
	{
		d->z_im = fabs(d->z_re * d->z_im) * -2.0;
		d->z_im += d->c_im;
		d->z_re = fabs(d->z_sre - d->z_sim) + d->c_re;
		d->z_sre = d->z_re * d->z_re;
		d->z_sim = d->z_im * d->z_im;
		d->n++;
	}
}

void		burn(t_fract *f, t_draw *d)
{
	while (d->z_sre + d->z_sim <= 4.0 && d->n < f->man->max_iter)
	{
		d->z_im = fabs(pow(d->z_im + d->z_re, 2) - d->z_sre - d->z_sim);
		d->z_im += d->c_im;
		d->z_re = fabs(d->z_sre - d->z_sim + d->c_re);
		d->z_sre = d->z_re * d->z_re;
		d->z_sim = d->z_im * d->z_im;
		d->n++;
	}
}

void	julia(t_fract *f, t_draw *d)
{
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

void		draw(t_fract *f)
{
	t_draw	*d;

	d = init_draw();
	while (d->y < HGHT)
	{
		d->c_im = f->man->min_im + d->y * f->man->cur_im;
		d->x = 0;
		while (d->x++ < WDTH)
		{
			d->c_re = f->man->min_re + d->x * f->man->cur_re;
			d->z_re = d->c_re;
			d->z_im = d->c_im;
			d->z_sre = d->z_re * d->z_re;
			d->z_sim = d->z_im * d->z_im;
			d->n = 0;
			fractals(f, d);
			(d->z_sre + d->z_sim > 4.0) ? (my_pixel_put_to_image(f->mlx->data, 
				f, d->x, d->y, d->n)) : (my_pixel_put_to_image2(f->mlx->data, f, d->x, d->y));
		}
		d->y++;
	}
	free(d);
}