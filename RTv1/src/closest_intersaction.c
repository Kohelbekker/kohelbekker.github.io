/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   closest_intersaction.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperesad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 13:56:18 by aperesad          #+#    #+#             */
/*   Updated: 2019/03/08 13:56:21 by aperesad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

void		take_param(t_sdl *sdl)
{
	sdl->closest_shape->type = sdl->shapes->type;
	sdl->closest_shape->axis_v = sdl->shapes->axis_v;
	sdl->closest_shape->center = sdl->shapes->center;
	sdl->closest_shape->radius = sdl->shapes->radius;
	sdl->closest_shape->color = sdl->shapes->color;
	sdl->closest_shape->specular = sdl->shapes->specular;
	sdl->closest_shape->angle = sdl->shapes->angle;
	sdl->closest_shape->clos_t = sdl->shapes->clos_t;
}

double		hit_loop(t_sdl *sdl, t_ray *ray, double t)
{
	double	*ts;

	if (sdl->shapes->type == 1)
		ts = hit_sphere(ray, sdl->shapes, 0.0, 0.0);
	else if (sdl->shapes->type == 3)
		ts = hit_cylinder(ray, sdl->shapes, 0.0, 0.0);
	else
		ts = hit_cone(ray, sdl->shapes, 0.0, 0.0);
	if (ts[0] < t && sdl->min < ts[0] && ts[0] < sdl->max)
	{
		t = ts[0];
		take_param(sdl);
		sdl->hit = 1;
	}
	if (ts[1] < t && sdl->min < ts[1] && ts[1] < sdl->max)
	{
		t = ts[1];
		take_param(sdl);
		sdl->hit = 1;
	}
	free(ts);
	return (t);
}

double		plane_t(t_sdl *sdl, t_ray *ray, double t)
{
	double	a;

	a = hit_plane(ray, sdl->shapes);
	if (a < t && sdl->min < a && a < sdl->max)
	{
		t = a;
		take_param(sdl);
		sdl->hit = 1;
	}
	return (t);
}

t_tmp		*clos_intersac(t_sdl *sdl, t_ray *ray, double min_t, double max_t)
{
	double	closest_t;
	t_shape	*head;

	sdl->min = min_t;
	sdl->max = max_t;
	sdl->hit = 0;
	closest_t = MAX_I;
	head = sdl->shapes;
	while (sdl->shapes)
	{
		if (sdl->shapes->type == 1 || sdl->shapes->type == 3 ||
			sdl->shapes->type == 4)
			closest_t = hit_loop(sdl, ray, closest_t);
		else if (sdl->shapes->type == 2)
			closest_t = plane_t(sdl, ray, closest_t);
		sdl->shapes = sdl->shapes->next;
	}
	if (sdl->hit == 1)
		sdl->closest_shape->clos_t = closest_t;
	else
		sdl->closest_shape->clos_t = -1.0;
	sdl->shapes = head;
	return (sdl->closest_shape);
}
