/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperesad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 15:53:46 by aperesad          #+#    #+#             */
/*   Updated: 2018/10/02 15:53:49 by aperesad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

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

t_mandel	*init_heart(char *av)
{
	t_mandel	*m;

	if (!(m = (t_mandel *)malloc(sizeof(t_mandel))))
		error("Error while allocating memory\n");
	m->name = av;
	m->start = 0;
	m->min_re = -2.5;
	m->max_re = 1.5;
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
