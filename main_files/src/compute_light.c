/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_light.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperesad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 18:28:21 by aperesad          #+#    #+#             */
/*   Updated: 2019/03/07 18:28:23 by aperesad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

double			ComputeLighting(t_sdl *sdl, t_vector point, t_vector normal, t_vector view)
{
	double		intensity;
	t_vector	vec_l;
	t_vector	vec_r;
	double		n_dot_l;
	double		r_dot_v;
	t_shape		*shape;
	t_ray		*tmp_ray;
	t_light		*head;

	intensity = 0.0;
	tmp_ray = (t_ray *)malloc(sizeof(t_ray));
	head = sdl->lights;
	while (sdl->lights)
	{
		if (sdl->lights->type == 0)
			intensity += sdl->lights->intensity;
		if (sdl->lights->type == 1)
		{
			vec_l = sdl->lights->position - point;
			tmp_ray->a = point;
			tmp_ray->b = vec_l;
			shape = ClosestIntersaction(sdl, tmp_ray, 0.00001, 1.0);
			if (shape->clos_t == -1.0)
			{	
				n_dot_l = dot(normal, vec_l);
				if (n_dot_l > 0)
					intensity += sdl->lights->intensity * n_dot_l / (v_length(normal) * v_length(vec_l));
				if (s > -1)
				{
					vec_r = (v_multi(2.0 * dot(normal, vec_l), normal) - vec_l);
					r_dot_v = dot(vec_r, view);
					if (r_dot_v > 0)
						intensity += sdl->lights->intensity * pow(r_dot_v / (v_length(vec_r) * v_length(view)), (double)s);
				}
			}
		}
		sdl->lights = sdl->lights->next;
	}
	sdl->lights = head;
	free(tmp_ray);
	return (intensity);
}