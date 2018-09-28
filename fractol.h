/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperesad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/17 12:53:58 by aperesad          #+#    #+#             */
/*   Updated: 2018/09/17 13:11:33 by aperesad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# define HGHT 1200
# define WDTH 1200

#include <math.h>
#include <mlx.h>
#include <fcntl.h>
#include <stdlib.h>
#include "libft/libft.h"
#include <pthread.h>

////////
#include <stdio.h>
////////

typedef struct s_draw
{
	double		c_im;
	double		c_re;
	double		z_re;
	double		z_im;
	double		z_sim;
	double		z_sre;
	int			n;
	int			y;
	int			x;
}				t_draw;

typedef struct s_mandel
{
	char		*name;
	double		min_im;
	double		max_im;
	double		min_re;
	double		max_re;
	double		cur_re;
	double		cur_im;
	double		jul_cr;
	double		jul_ci;
	int			max_iter;
	int			start;
}				t_mandel;

typedef struct	s_mlx
{
	void		*mlx_p;
	void		*win_p;
	void		*img;
	char		*data;
	int			bpp;
	int			sl;
	int			endian;
}				t_mlx;

typedef struct s_fract
{
	t_mlx		*mlx;
	t_mandel	*man;
	double		zoom;
	double		k;
	double		k_ind1;
	double		k_ind2;
	double		k_ind3;
	double		c_ind;
	int			byte_ind;
	int			byte_c;
	int			flag;
}				t_fract;

void		fractals(t_fract *f, t_draw *d);
int			exit_x(void);
int			error1(t_fract *f, char *str);
int			error(char *str);
t_mlx		*mlx_clean(t_mlx *mlx);
void		find_fract(t_fract *f, char *av);
void		init(t_fract *f, char *av);
int			main(int ac, char **av);
void   		my_pixel_put_to_image(char *data, t_fract *f, int x, int y, int n);
void    	my_pixel_put_to_image2(char *data, t_fract *f, int x, int y);
int			mouse_julia(int x, int y, t_fract *f);
int				hooks(int key, t_fract *f);
t_mandel	*init_burn(char *av);
t_mandel	*init_mandel(char *av);
t_mandel	*init_julia(char *av);
t_draw		*init_draw();
void			mandelbrot(t_fract *f, t_draw *d);
void		heart(t_fract	*f, t_draw *d);
void		tricorn(t_fract *f, t_draw *d);
void		burn(t_fract	*f, t_draw *d);
void		buffalo(t_fract	*f, t_draw *d);
void		draw(t_fract	*f);
void		julia(t_fract *f, t_draw *d);
void			rotation(int key, t_fract *f);
t_mandel	*init_buffalo(char *av);
void		switch_color(int key, t_fract *f);

void		find_fract(t_fract *f, char *av);
int			zoom_hook(int key, int x, int y, t_fract *f);



#endif