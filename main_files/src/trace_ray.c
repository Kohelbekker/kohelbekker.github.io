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

t_shape		*ClosestIntersaction(t_sdl *sdl, t_ray *ray, double min_t, double max_t)
{
	double		closest_t;
	int			hit = 0;
	double		*ts;
	t_shape		*head;
	double		a;	
	t_shape		*closest_shape;

	closest_t = MAX_I;
	head = sdl->shapes;
	while (sdl->shapes)
	{

		if (sdl->shapes->type == 1 || sdl->shapes->type == 3 || sdl->shapes->type == 4)
		{
			if (sdl->shapes->type == 1)
				ts = hit_sphere(ray, sdl->shapes);
			else if (sdl->shapes->type == 3)
				ts = hit_cylinder(ray, sdl->shapes);
			else
				ts = hit_cone(ray, sdl->shapes);
			if (ts[0] < closest_t && min_t < ts[0] && ts[0] < max_t)
			{
				closest_t = ts[0];
				closest_shape = sdl->shapes;

				hit = 1;
			}
			if (ts[1] < closest_t && min_t < ts[1] && ts[1] < max_t)
			{
				closest_t = ts[1];
				closest_shape = sdl->shapes;
				hit = 1;
			}
			free(ts);
		}
		else if (sdl->shapes->type == 2)
		{
			a = hit_plane(ray, sdl->shapes);  
			if (a < closest_t && min_t < a && a < max_t)
			{
				closest_t = a;
				closest_shape = sdl->shapes;
				hit = 1;
			}
		}
		sdl->shapes = sdl->shapes->next;		
	}
	if (hit == 1)
		closest_shape->clos_t = closest_t;
	else
	{
		closest_shape = (t_shape *)malloc(sizeof(t_shape));
		closest_shape->clos_t = -1.0;
	}
	sdl->shapes = head;
	return (closest_shape);
}

t_vector	TraceRay(t_sdl *sdl, t_ray *ray, double min_t, double max_t)
{
	t_vector	point;
	t_vector	normal;
	t_vector	view;
	t_shape		*closest_shape;
	double		light_power;
	
	closest_shape = ClosestIntersaction(sdl, sdl->ray, min_t, max_t);
	if (closest_shape->clos_t == -1.0)
		return (sdl->background);

	point = point_vector(closest_shape->clos_t, ray);
	if (closest_shape->type == 1)
		normal = unit_vector(point - closest_shape->center);
	else if (closest_shape->type == 2)
	{
		if (dot(ray->b, closest_shape->axis_v) < 0)
			normal = closest_shape->axis_v;
		else
			normal = -closest_shape->axis_v;
	}
	else if (closest_shape->type == 3)
	{
		normal = unit_vector(point - closest_shape->center - v_multi((dot(ray->b, closest_shape->axis_v) *
			closest_shape->clos_t +  dot(ray->a - closest_shape->center, closest_shape->axis_v)), closest_shape->axis_v));
	}
	else if (closest_shape->type == 4)
	{
		normal = unit_vector(point - closest_shape->center - v_multi((1 + pow(sin(closest_shape->angle * DEG) / cos(closest_shape->angle * DEG), 2)) *
			(dot(ray->b, closest_shape->axis_v) * closest_shape->clos_t + dot(ray->a - closest_shape->center, closest_shape->axis_v)), closest_shape->axis_v));
	}
	view = v_multi(-1, ray->b);
	light_power = ComputeLighting(sdl, point, normal, view, closest_shape->specular);
	return (v_multi(light_power, closest_shape->color));
}
