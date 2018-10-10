/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperesad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 17:22:55 by aperesad          #+#    #+#             */
/*   Updated: 2018/10/08 17:22:57 by aperesad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_H
# define WOLF_H

# define HGHT 800
# define WDTH 800

#include <math.h>
#include <mlx.h>
#include <stdlib.h>
#include "libft/libft.h"
#include <fcntl.h>

typedef struct	s_mlx
{
	void		*mlx_p;
	void		*win_p;
	void		*img;
	char		*data;
	int			bpp;
	int			sl;
	int			ed;
	int			color;
}				t_mlx;

typedef struct	s_wolf
{
	t_mlx		*mlx;
	int			count;
	double		cam_OX;
	double		x_ray;
	double		y_ray;
	int			x;
	int			y;
	double		OXdist;
	double		OYdist;
	double		deltaOX;
	double		deltaOY;
	double		wallDist;
	int			stepX;
	int			stepY;
	int			hit;
	int			side;
	int			line_h;
	int			wall_start;
	int			wall_end;

	double		posX;
	double		posY;
	double		vect_X;
	double		vect_Y;
	double		planeX;
	double		planeY;
}				t_wolf;




#endif
