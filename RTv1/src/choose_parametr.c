/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   choose_parametr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperesad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 13:41:11 by aperesad          #+#    #+#             */
/*   Updated: 2019/03/08 13:41:15 by aperesad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

void			param1(t_sdl *sdl, t_shape *tmp, char **word, int i)
{
	if (i == 1)
		shape_center(sdl, tmp, word);
	else if (i == 2)
		shape_radius(sdl, tmp, word);
	else if (i == 3)
		shape_color(sdl, tmp, word);
	else if (i == 4)
		shape_specular(sdl, tmp, word);
}

void			param2(t_sdl *sdl, t_shape *tmp, char **word, int i)
{
	if (i == 1)
		shape_center(sdl, tmp, word);
	else if (i == 2)
		shape_axis(sdl, tmp, word);
	else if (i == 3)
		shape_color(sdl, tmp, word);
}

void			param3(t_sdl *sdl, t_shape *tmp, char **word, int i)
{
	if (i == 1)
		shape_center(sdl, tmp, word);
	else if (i == 2)
		shape_axis(sdl, tmp, word);
	else if (i == 3)
		shape_color(sdl, tmp, word);
	else if (i == 4)
		shape_angle(sdl, tmp, word);
	else if (i == 5)
		shape_specular(sdl, tmp, word);
}

void			param4(t_sdl *sdl, t_shape *tmp, char **word, int i)
{
	if (i == 1)
		shape_center(sdl, tmp, word);
	else if (i == 2)
		shape_axis(sdl, tmp, word);
	else if (i == 3)
		shape_color(sdl, tmp, word);
	else if (i == 4)
		shape_radius(sdl, tmp, word);
	else if (i == 5)
		shape_specular(sdl, tmp, word);
}
