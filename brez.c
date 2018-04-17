#include "fdf.h"
#include "mlx.h"
#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int sign(int a, int b)
{
	if (a - b > 0)
		return (1);
	if (a - b < 0 )
		return (-1);
	else
		return(0);
}

void swap(int *a, int *b)
{
	int tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	swap_s_e(int xs, int ys, int xe, int ye)
{
	swap(&xe, &xs);
	swap(&ye, &ys);
}

int		point(int xs, int ys, t_mlx *mlx)
{
	mlx_pixel_put(mlx->mlx_p, mlx->win_p, xs, ys, 0xFFFFFF);
	return(0);
}

typedef struct	s_brez
{
	int		sign_x;
	int		sign_y;
	int		e;
	int		dx;
	int		dy;
	int		change;
}			t_brez;

int		draw_l(int xs, int ys, int xe, int ye, t_mlx *mlx)
{
	t_brez	b;

	if (ye == ys && xs == xe)
	{
		point(xs, ys, mlx);
		return(0);
	}
	if (xe < xs)
		swap_s_e(xs, ys, xe, ye);
	b.dx = abs(xe - xs);
	b.dy = abs(ye - ys);
	b.sign_x = sign(xe, xs);
	b.sign_y = sign(ye, ys);
	if (b.dy > b.dx)
	{
		swap (&(b.dx),&(b.dy));
		b.change = 1;
	}
	else
		b.change = 0;
	b.e = 2 * b.dy - b.dx;
	while (xs != (xe + 1))
	{
		mlx_pixel_put(mlx->mlx_p, mlx->win_p, xs, ys, 0xFFFFFF);
		while (b.e >= 0)
		{
			if (b.change == 1)
				xs += b.sign_x;
			else
				ys += b.sign_y;
			b.e = b.e - 2*(b.dx);
		}
		if (b.change == 1)
			ys += b.sign_y;
		else
			xs += b.sign_x;
		b.e = b.e+2*(b.dy);
	}
	return (0);
}

/*int main()
{
	t_a	*a;
	a->mlx_p = mlx_init();
	a->win_p = mlx_new_window(a->mlx_p, 500, 500, "mlx 42");
	mlx_pixel_put(a->mlx_p, a->win_p, 250, 250, 0xFFFFFF);
	draw(1, 1, 200, 400, a);
	mlx_hook(a->win_p, 17, 1L << 17, exit_x, a);
	mlx_loop(a->mlx_p);
	return (0);
}*/
