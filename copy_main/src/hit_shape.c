/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_shape.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperesad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 18:29:35 by aperesad          #+#    #+#             */
/*   Updated: 2019/03/07 18:29:37 by aperesad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

double			*hit_sphere(t_ray *ray, t_shape *shape, double a, double b)
{
	t_vector	oc;
	double		c;
	double		disc;
	double		*xs;

	xs = (double *)malloc(sizeof(double) * 2);
	xs[0] = MAX_I;
	xs[1] = MAX_I;
	oc = (ray->a - shape->center);
	a = dot(ray->b, ray->b);
	b = 2 * dot(oc, ray->b);
	c = dot(oc, oc) - shape->radius * shape->radius;
	disc = b * b - 4 * a * c;
	if (disc >= 0)
	{
		xs[0] = (-b + sqrt(disc)) / (2.0 * a);
		xs[1] = (-b - sqrt(disc)) / (2.0 * a);
	}
	return (xs);
}

double			hit_plane(t_ray *ray, t_shape *shape)
{
	t_vector	oc;
	double		a;
	double		b;
	double		result;

	oc = ray->a - shape->center;
	a = -(dot(oc, shape->axis_v));
	b = dot(ray->b, shape->axis_v);
	if (b == 0)
		return (-1.0);
	result = a / b;
	return (result);
}

double			*hit_cylinder(t_ray *ray, t_shape *shape, double a, double b)
{
	t_vector	oc;
	double		*xs;
	double		c;
	double		disc;

	xs = (double *)malloc(sizeof(double) * 2);
	xs[0] = MAX_I;
	xs[1] = MAX_I;
	oc = ray->a - shape->center;
	a = dot(ray->b, ray->b) - pow(dot(ray->b, shape->axis_v), 2);
	b = 2 * (dot(ray->b, oc) - (dot(ray->b, shape->axis_v) *
		dot(oc, shape->axis_v)));
	c = dot(oc, oc) - pow(dot(oc, shape->axis_v), 2) -
	shape->radius * shape->radius;
	disc = b * b - 4 * a * c;
	if (disc >= 0)
	{
		xs[0] = (-b + sqrt(disc)) / (2.0 * a);
		xs[1] = (-b - sqrt(disc)) / (2.0 * a);
	}
	return (xs);
}

double			*hit_cone(t_ray *ray, t_shape *shape, double a, double b)
{
	t_vector	oc;
	double		*xs;
	double		c;
	double		e;
	double		disc;

	xs = (double *)malloc(sizeof(double) * 2);
	xs[0] = MAX_I;
	xs[1] = MAX_I;
	oc = ray->a - shape->center;
	e = (1 + pow(sin(DEG * shape->angle) / cos(DEG * shape->angle), 2));
	a = dot(ray->b, ray->b) - e * pow(dot(ray->b, shape->axis_v), 2);
	b = 2 * (dot(ray->b, oc) - e * (dot(ray->b, shape->axis_v) *
		dot(oc, shape->axis_v)));
	c = dot(oc, oc) - e * (pow(dot(oc, shape->axis_v), 2));
	disc = b * b - 4 * a * c;
	if (disc >= 0)
	{
		xs[0] = (-b + sqrt(disc)) / (2.0 * a);
		xs[1] = (-b - sqrt(disc)) / (2.0 * a);
	}
	return (xs);
}
