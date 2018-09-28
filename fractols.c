#include "fractol.h"

void   		my_pixel_put_to_image(char *data, t_fract *f, int x, int y, int n)
{
	int		index;
	unsigned char a;
	unsigned char b;
	unsigned char c;

	index = n + 1 - (log(2) / 1.0) / log (2);
	a = (sin(f->k_ind1 * index + f->c_ind) * f->byte_ind + f->byte_c);
	b = (sin(f->k_ind2 * index + f->c_ind) * f->byte_ind + f->byte_c);
	c = (sin(f->k_ind3 * index + f->c_ind) * f->byte_ind + f->byte_c);
	data[y * f->mlx->sl + x * f->mlx->bpp / 8] = a;
	data[y * f->mlx->sl + x * f->mlx->bpp / 8 + 1] = b;
	data[y * f->mlx->sl + x * f->mlx->bpp / 8 + 2] = c;
}

void    my_pixel_put_to_image2(char *data, t_fract *f, int x, int y)
{
	int color;

	color =  0x000000;

	data[y * f->mlx->sl + x * f->mlx->bpp / 8] = color;
	data[y * f->mlx->sl + x * f->mlx->bpp / 8 + 1] = color >> 8;
	data[y * f->mlx->sl + x * f->mlx->bpp / 8 + 2] = color >> 16;
}

int			mouse_julia(int x, int y, t_fract *f)
{
	if (ft_strcmp(f->man->name, "julia") == 0)
	{
		if ((x < WDTH && x >= 0) && (y < HGHT && y >= 0) && f->flag == 0)
		{
			f->man->jul_cr = (double)x / (double)(WDTH);
			f->man->jul_ci = (double)y / (double)(HGHT);
			draw(f);
			mlx_put_image_to_window(f->mlx->mlx_p, f->mlx->win_p, f->mlx->img, 0, 0);
		}
	}
	return (0);
}

void		scale(double re, double im, t_fract *f)
{
	f->k = 1.0 / f->zoom;
	f->man->min_re = re + (f->man->min_re - re) * f->k;
    f->man->min_im = im + (f->man->min_im - im) * f->k;
    f->man->max_re = re + (f->man->max_re - re) * f->k;
    f->man->max_im = im + (f->man->max_im - im) * f->k;
    f->man->cur_re = (f->man->max_re - f->man->min_re) / (WDTH - 1);
	f->man->cur_im = (f->man->max_im - f->man->min_im) / (HGHT - 1);
}

int			zoom_hook(int key, int x, int y, t_fract *f)
{
	double re;
	double im;

	re = (double)x / ((double)WDTH / (f->man->max_re - f->man->min_re)) 
	+ f->man->min_re;
	im = (double)y / ((double)HGHT / (f->man->max_im - f->man->min_im)) 
	+ f->man->min_im;
	f->zoom = 1.0;
	if (key == 1 || key == 4)
	{
		(key == 1) ? (f->man->max_iter += 4) : (f->man->max_iter++);
		(key == 1) ? (f->zoom = 3.0) : (f->zoom = 1.25);
		(key == 1) ? (f->man->start += 4) : (f->man->start++);
		scale(re, im, f);	
	}
	if ((key == 2 || key == 5) && f->man->start > -4)
	{
		(key == 2) ? (f->zoom = 1.0/3.0) : (f->zoom = 0.8);
		(key == 2) ? (f->man->start -= 3) : (f->man->start--);
		(key == 2) ? (f->man->max_iter -= 2) : (f->man->max_iter--);
		scale(re, im, f);	
	}
	draw(f);
	mlx_put_image_to_window(f->mlx->mlx_p, f->mlx->win_p, f->mlx->img, 0, 0);
	return (0);
}

void			rotation(int key, t_fract *f)
{
	if (key == 123)
	{
		f->man->min_re -= 30 * f->man->cur_re;
		f->man->max_re -= 30 * f->man->cur_re;
	}
	if (key == 126)
	{
		f->man->min_im -= 30 * f->man->cur_im;
		f->man->max_im -= 30 * f->man->cur_im;
	}
	if (key == 124)
	{
		f->man->min_re += 30 * f->man->cur_re;
		f->man->max_re += 30 * f->man->cur_re;
	}
	if (key == 125)
	{
		f->man->min_im += 30 * f->man->cur_im;
		f->man->max_im += 30 * f->man->cur_im;
	}
}

void		iterations(int key, t_fract *f)
{
	if (key == 69)
		f->man->max_iter += 10;
	else if (key == 78 && f->man->max_iter > 0)
		f->man->max_iter -= 10;
}

void		switch_color(int key, t_fract *f)
{
	(key == 18 || key == 19) ? (f->byte_ind = 230) : (f->byte_ind = 255);
	if (key == 18)
	{
		f->k_ind1 = 0.25;
		f->k_ind2 = 0.4;
		f->k_ind3 = 0.12;
		f->c_ind = 4;
		f->byte_c = 25;
	}
	if (key == 20 || key  == 21)
	{
		f->k_ind1 = 0.08;
		f->k_ind2 = 0.04;
		f->k_ind3 = 0.012;
		f->c_ind = 1;
		(key == 20) ? (f->byte_c = 50) : (f->byte_c = (rand() % 255 + 1));
	}
	if (key == 19)
	{
		f->k_ind1 = 0.016;
		f->k_ind2 = 0.016;
		f->k_ind3 = 0.016;
		f->c_ind = 4;
		f->byte_c = 50;
	}
}

void		get_back(t_fract *f)
{
	char	*av;

	av = f->man->name;
	find_fract(f, av);
	f->k_ind1 = 0.08;
	f->k_ind2 = 0.04;
	f->k_ind3 = 0.012;
	f->c_ind = 1;
	f->byte_ind = 255;
	f->byte_c = 50;
	f->flag = 0;
}

int				hooks(int key, t_fract *f)
{
	if (key == 53)
	{
		mlx_clean(f->mlx);
		system("leaks a.out -q");
		exit(0);
	}
	if (key == 123 || key == 124 || key == 125 || key == 126)
		rotation(key, f);
	if (key == 69 || key == 78)
		iterations(key, f);
	if (key == 18 || key == 19 || key == 20 || key == 21)
		switch_color(key, f);
	if (key == 36)
		get_back(f);
	draw(f);
	mlx_put_image_to_window(f->mlx->mlx_p, f->mlx->win_p, f->mlx->img, 0, 0);
	if (key == 49)
		(f->flag == 0) ? (f->flag = 1) : (f->flag = 0);
	return (0);
}

t_mandel	*init_burn(char *av)
{
	t_mandel	*m;

	if (!(m = (t_mandel *)malloc(sizeof(t_mandel))))
		error("Error while allocating memory\n");
	m->name = av;
	m->start = 0;
	m->min_re = -2.0;
	m->max_re = 1.2;
	m->min_im = -2.0;
	m->max_im = 1.2;
	m->max_iter = 30;
	m->cur_re = (m->max_re - m->min_re) / (WDTH - 1);
	m->cur_im = (m->max_im - m->min_im) / (HGHT - 1);
	return (m);
}

t_mandel	*init_mandel(char *av)
{
	t_mandel	*m;

	if (!(m = (t_mandel *)malloc(sizeof(t_mandel))))
		error("Error while allocating memory\n");
	m->name = av;
	m->start = 0;
	m->min_re = -2.0;
	m->max_re = 1.0;
	m->min_im = 1.5;
	m->max_im = -1.5;
	m->max_iter = 30;
	m->cur_re = (m->max_re - m->min_re) / (WDTH - 1);
	m->cur_im = (m->max_im - m->min_im) / (HGHT - 1);
	return (m);
}

t_mandel	*init_buffalo(char *av)
{
	t_mandel	*m;

	if (!(m = (t_mandel *)malloc(sizeof(t_mandel))))
		error("Error while allocating memory\n");
	m->name = av;
	m->start = 0;
	m->min_re = -2.2;
	m->max_re = 0.8;
	m->min_im = 2.0;
	m->max_im = -1.0;
	m->max_iter = 30;
	m->cur_re = (m->max_re - m->min_re) / (WDTH - 1);
	m->cur_im = (m->max_im - m->min_im) / (HGHT - 1);
	return (m);
}

t_mandel	*init_julia(char *av)
{
	t_mandel	*m;

	if (!(m = (t_mandel *)malloc(sizeof(t_mandel))))
		error("Error while allocating memory\n");
	m->name = av;
	m->start = 0;
	m->min_re = -2.0;
	m->max_re = 2.0;
	m->max_im = -2.0;
	m->min_im = 2.0;
	m->max_iter = 30;
	m->cur_re = (m->max_re - m->min_re) / (WDTH - 1);
	m->cur_im = (m->max_im - m->min_im) / (HGHT - 1);
	m->jul_cr = -0.7;
	m->jul_ci = 0.27015;
	return (m);
}
