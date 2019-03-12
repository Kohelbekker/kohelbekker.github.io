/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_ray.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperesad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 18:26:35 by aperesad          #+#    #+#             */
/*   Updated: 2019/03/07 18:26:37 by aperesad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

void			shape2_calc(t_sdl *sdl, t_ray *ray, t_tmp *closest_shape)
{
	if (dot(ray->b, closest_shape->axis_v) < 0)
		sdl->calc->normal = closest_shape->axis_v;
	else
		sdl->calc->normal = -closest_shape->axis_v;
}

void			shape4_calc(t_sdl *sdl, t_ray *ray, t_tmp *closest_shape)
{
	double		a;
	double		b;
	double		c;
	t_vector	d;
	t_vector	e;

	a = (1 + pow(sin(closest_shape->angle * DEG) /
		cos(closest_shape->angle * DEG), 2));
	b = dot(ray->a - closest_shape->center, closest_shape->axis_v);
	c = (dot(ray->b, closest_shape->axis_v) * closest_shape->clos_t + b);
	d = v_multi(a * c, closest_shape->axis_v);
	e = sdl->calc->point - closest_shape->center;
	sdl->calc->normal = unit_vector(e - d);
}

void			shape3_calc(t_sdl *sdl, t_ray *ray, t_tmp *closest_shape)
{
	double		a;
	double		b;
	t_vector	c;

	a = dot(ray->b, closest_shape->axis_v) * closest_shape->clos_t;
	b = dot(ray->a - closest_shape->center, closest_shape->axis_v);
	c = sdl->calc->point - closest_shape->center;
	sdl->calc->normal = unit_vector(c - v_multi((a + b),
		closest_shape->axis_v));
}

t_vector		trace_ray(t_sdl *sdl, t_ray *ray, double min_t, double max_t)
{
	t_tmp		*closest_shape;
	double		light_power;
	t_vector	color;

	closest_shape = clos_intersac(sdl, sdl->ray, min_t, max_t);
	if (closest_shape->clos_t == -1.0)
		return (sdl->background);
	sdl->calc->point = point_vector(closest_shape->clos_t, ray);
	if (closest_shape->type == 1)
		sdl->calc->normal = unit_vector(sdl->calc->point -
			closest_shape->center);
	else if (closest_shape->type == 2)
		shape2_calc(sdl, ray, closest_shape);
	else if (closest_shape->type == 3)
		shape3_calc(sdl, ray, closest_shape);
	else if (closest_shape->type == 4)
		shape4_calc(sdl, ray, closest_shape);
	sdl->calc->view = v_multi(-1, ray->b);
	color = closest_shape->color;
	light_power = compute_lighting(sdl, closest_shape->specular, 0.0);
	if (light_power > 1)
		light_power = 1.0;
	return (v_multi(light_power, color));
}
