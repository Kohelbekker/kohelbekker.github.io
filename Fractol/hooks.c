/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperesad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 15:50:43 by aperesad          #+#    #+#             */
/*   Updated: 2018/10/02 15:53:39 by aperesad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		rotation(int key, t_fract *f)
{
	if (key == 123)
	{
		f->man->min_re -= 40 * f->man->cur_re;
		f->man->max_re -= 40 * f->man->cur_re;
	}
	if (key == 126)
	{
		f->man->min_im -= 40 * f->man->cur_im;
		f->man->max_im -= 40 * f->man->cur_im;
	}
	if (key == 124)
	{
		f->man->min_re += 40 * f->man->cur_re;
		f->man->max_re += 40 * f->man->cur_re;
	}
	if (key == 125)
	{
		f->man->min_im += 40 * f->man->cur_im;
		f->man->max_im += 40 * f->man->cur_im;
	}
}

void		iterations(int key, t_fract *f)
{
	if (key == 69)
		f->man->max_iter += 5;
	else if (key == 78 && f->man->max_iter > 0)
		f->man->max_iter -= 5;
}

void		switch_color(int key, t_fract *f)
{
	f->byte_ind = ((key == 18 || key == 19) ? 230 : 255);
	if (key == 18)
	{
		f->k_ind1 = 0.25;
		f->k_ind2 = 0.4;
		f->k_ind3 = 0.12;
		f->c_ind = 4;
		f->byte_c = 25;
	}
	if (key == 20 || key == 21)
	{
		f->k_ind1 = 0.08;
		f->k_ind2 = 0.04;
		f->k_ind3 = 0.012;
		f->c_ind = 1;
		f->byte_c = ((key == 20) ? 50 : ((rand() % 255 + 1)));
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
	free(f->man);
	find_fract(f, av);
	f->k_ind1 = 0.08;
	f->k_ind2 = 0.04;
	f->k_ind3 = 0.012;
	f->c_ind = 1;
	f->byte_ind = 255;
	f->byte_c = 50;
	f->flag = 0;
}

int			hooks(int key, t_fract *f)
{
	if (key == 53)
	{
		mlx_clean(f->mlx);
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
	my_threads(f);
	mlx_put_image_to_window(f->mlx->mlx_p, f->mlx->win_p, f->mlx->img, 0, 0);
	if (key == 49)
		f->flag = ((f->flag == 0) ? 1 : 0);
	return (0);
}
