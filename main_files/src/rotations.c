/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotations.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperesad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 19:00:48 by aperesad          #+#    #+#             */
/*   Updated: 2019/03/07 19:00:51 by aperesad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

t_vector			rot(t_vector a, t_sdl *sdl)
{
	double		tmp_x;
	double		tmp_y;
	double		tmp_z;


	tmp_x = a[0];
	tmp_y = a[1];
	tmp_z = a[2];
	a[0] = x_part(sdl, tmp_x, tmp_y, tmp_z);
	a[1] = y_part(sdl, tmp_x, tmp_y, tmp_z);
	a[2] = z_part(sdl, tmp_x, tmp_y, tmp_z);
	return (a);
}

double			x_part(t_sdl *sdl, double x, double y, double z)
{
	double		i;
	double		j;
	double		k;
	double		a;
	double		b;
	double		c;
	double		res;

	a = sdl->cam_rot[0] * DEG;
	b = sdl->cam_rot[1] * DEG;
	c = sdl->cam_rot[2] * DEG;

	i = cos(b) * cos(c) * x;
	j = -cos(b) * sin(c) * y;
	k = sin(b) * z;
	res = i + j + k;
	return(res);
}

double			y_part(t_sdl *sdl, double x, double y, double z)
{
	double		i;
	double		j;
	double		k;
	double		a;
	double		b;
	double		c;
	double		res;

	a = sdl->cam_rot[0] * DEG;
	b = sdl->cam_rot[1] * DEG;
	c = sdl->cam_rot[2] * DEG;

	i = (sin(a) * sin(b) * cos(c) + cos(a) * sin(c)) * x;
	j = ((-sin(a)) * sin(b) * sin(c) + cos(a) * cos(c)) * y;
	k = (-sin(a)) * cos(b) * z;
	res = i + j + k;
	return(res);
}

double			z_part(t_sdl *sdl, double x, double y, double z)
{
	double		i;
	double		j;
	double		k;
	double		a;
	double		b;
	double		c;
	double		res;

	a = sdl->cam_rot[0] * DEG;
	b = sdl->cam_rot[1] * DEG;
	c = sdl->cam_rot[2] * DEG;

	i = ((-cos(a)) * sin(b) * cos(c) + sin(a) * sin(c)) * x;
	j = (cos(a) * sin(b) * sin(c) + sin(a) * cos(c)) * y;
	k = cos(a) * cos(b) * z;
	res = i + j + k;
	return(res);
}
