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

int			mouse_julia(int x, int y, t_fract *f)
{
	if (ft_strcmp(f->man->name, "julia") == 0)
	{
		if ((x < WDTH && x >= 0) && (y < HGHT && y >= 0) && f->flag == 0)
		{
			f->man->jul_cr = (double)x / (double)(WDTH);
			f->man->jul_ci = (double)y / (double)(HGHT);
			my_threads(f);
			mlx_put_image_to_window(f->mlx->mlx_p, f->mlx->win_p,
				f->mlx->img, 0, 0);
		}
	}
	return (0);
}
