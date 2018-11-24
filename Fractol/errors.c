/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperesad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 15:53:24 by aperesad          #+#    #+#             */
/*   Updated: 2018/10/02 15:53:26 by aperesad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int			exit_x(void)
{
	exit(1);
	return (0);
}

int			error1(t_fract *f, char *str)
{
	ft_putendl(str);
	mlx_clean(f->mlx);
	exit(1);
	return (0);
}

int			error(char *str)
{
	ft_putendl(str);
	exit(1);
	return (0);
}

t_mlx		*mlx_clean(t_mlx *mlx)
{
	if (mlx->win_p != NULL)
		mlx_destroy_window(mlx->mlx_p, mlx->win_p);
	if (mlx->img != NULL)
		mlx_destroy_image(mlx->mlx_p, mlx->img);
	free(mlx);
	return (0);
}
