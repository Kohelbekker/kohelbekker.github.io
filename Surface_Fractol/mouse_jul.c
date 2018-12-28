/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_jul.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperesad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 15:52:37 by aperesad          #+#    #+#             */
/*   Updated: 2018/10/02 15:52:42 by aperesad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int			mouse_julia(t_fract *f)
{
	if (ft_strcmp(f->man->name, "julia") == 0)
	{
		int		x;
		int		y;
		int		a;

		x = f->mlx->mlx_p.motion.x;
		y = f->mlx->mlx_p.motion.y;
		a = f->mlx->mlx_p.button.button;
		if ((x < WDTH && x >= 0) && (y < HGHT && y >= 0) && f->flag == 0)
		{
			f->man->jul_cr = (double)x / (double)(WDTH);
			f->man->jul_ci = (double)y / (double)(HGHT);
			draw(f);
		}
	}
	return (0);
}
