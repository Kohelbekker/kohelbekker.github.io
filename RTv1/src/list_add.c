/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_add.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperesad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 18:36:47 by aperesad          #+#    #+#             */
/*   Updated: 2019/03/07 18:36:49 by aperesad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

t_shape			*add_list(t_sdl *sdl, t_shape *new)
{
	t_shape		*first;

	first = sdl->shapes;
	if (sdl->shapes)
	{
		while (sdl->shapes->next != NULL)
			sdl->shapes = sdl->shapes->next;
		sdl->shapes->next = new;
		return (first);
	}
	return (new);
}

t_light			*add_light(t_sdl *sdl, t_light *new)
{
	t_light		*first;

	first = sdl->lights;
	if (sdl->lights)
	{
		while (sdl->lights->next != NULL)
			sdl->lights = sdl->lights->next;
		sdl->lights->next = new;
		return (first);
	}
	return (new);
}
