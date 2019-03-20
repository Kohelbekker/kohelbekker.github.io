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

double			compute_lighting(t_sdl *sdl, int s, double intensity)
{
	t_tmp		*shape;
	t_ray		*tmp_ray;
	t_light		*head;

	tmp_ray = (t_ray *)malloc(sizeof(t_ray));
	head = sdl->lights;
	while (sdl->lights)
	{
		if (sdl->lights->type == 0 && intensity < 1.0)
			intensity += sdl->lights->intensity;
		if (sdl->lights->type == 1)
		{
			sdl->calc->vec_l = sdl->lights->position - sdl->calc->point;
			tmp_ray->a = sdl->calc->point;
			tmp_ray->b = sdl->calc->vec_l;
			shape = clos_intersac(sdl, tmp_ray, 0.00001, 1.0);
			if (shape->clos_t == -1.0)
				intensity = light_loop(sdl, s, intensity);
		}
		sdl->lights = sdl->lights->next;
	}
	sdl->lights = head;
	free(tmp_ray);
	return (intensity);
}

double			light_loop(t_sdl *sdl, int s, double intensity)
{
	sdl->calc->n_dot_l = dot(sdl->calc->normal, sdl->calc->vec_l);
	if (sdl->calc->n_dot_l > 0 && intensity < 1.0)
		intensity += sdl->lights->intensity * sdl->calc->n_dot_l /
	(v_length(sdl->calc->normal) * v_length(sdl->calc->vec_l));
	if (s > -1)
	{
		sdl->calc->vec_r = (v_multi(2.0 * dot(sdl->calc->normal,
			sdl->calc->vec_l), sdl->calc->normal) - sdl->calc->vec_l);
		sdl->calc->r_dot_v = dot(sdl->calc->vec_r, sdl->calc->view);
		if (sdl->calc->r_dot_v > 0 && intensity < 1.0)
			intensity += sdl->lights->intensity *
		pow(sdl->calc->r_dot_v / (v_length(sdl->calc->vec_r) *
			v_length(sdl->calc->view)), (double)s);
	}
	return (intensity);
}
