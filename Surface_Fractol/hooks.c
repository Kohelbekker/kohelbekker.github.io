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

void		rotation(int a, t_fract *f)
{
	if (a == SDLK_LEFT)
	{
		f->man->min_re -= 40 * f->man->cur_re;
		f->man->max_re -= 40 * f->man->cur_re;
	}
	if (a == SDLK_UP)
	{
		f->man->min_im -= 40 * f->man->cur_im;
		f->man->max_im -= 40 * f->man->cur_im;
	}
	if (a == SDLK_RIGHT)
	{
		f->man->min_re += 40 * f->man->cur_re;
		f->man->max_re += 40 * f->man->cur_re;
	}
	if (a == SDLK_DOWN)
	{
		f->man->min_im += 40 * f->man->cur_im;
		f->man->max_im += 40 * f->man->cur_im;
	}
}

void		iterations(int key, t_fract *f)
{
	if (key == SDLK_KP_PLUS)
		f->man->max_iter += 5;
	else if (key == SDLK_KP_MINUS && f->man->max_iter > 0)
		f->man->max_iter -= 5;
}

void		switch_color(int key, t_fract *f)
{
	f->byte_ind = ((key == SDLK_1 || key == SDLK_2) ? 230 : 255);
	if (key == SDLK_1)
	{
		f->k_ind1 = 0.25;
		f->k_ind2 = 0.4;
		f->k_ind3 = 0.12;
		f->c_ind = 4;
		f->byte_c = 25;
	}
	if (key == SDLK_3 || key == SDLK_4)
	{
		f->k_ind1 = 0.08;
		f->k_ind2 = 0.04;
		f->k_ind3 = 0.012;
		f->c_ind = 1;
		f->byte_c = ((key == 20) ? 50 : ((rand() % 255 + 1)));
	}
	if (key == SDLK_2)
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

int			hooks(t_fract *f)
{
	int a = f->mlx->mlx_p.key.keysym.sym;
	if (f->mlx->mlx_p.type == SDL_QUIT || a == SDLK_ESCAPE)
	{
		f->exit = 1;
		mlx_clean(f->mlx);
		return(0);
	}
	if (a == SDLK_LEFT || a == SDLK_RIGHT || a == SDLK_DOWN || a == SDLK_UP)
		rotation(a, f);
	if (a == SDLK_KP_PLUS || a == SDLK_KP_MINUS)
		iterations(a, f);
	if (a == SDLK_1 || a == SDLK_2 || a == SDLK_3 || a == SDLK_4)
		switch_color(a, f);
	if (a == SDLK_RETURN)
		get_back(f);
	if (a == SDLK_SPACE)
		f->flag = ((f->flag == 0) ? 1 : 0);
	draw(f);
	return (0);
}
