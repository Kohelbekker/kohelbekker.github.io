#ifndef FDF_H
# define FDF_H

# define HEIGHT
# define WIDTH
# define SPACE(x) (x == ' ' || x == '\t' || x == '\n') 

#include <mlx.h>
#include <fcntl.h>
#include "libft/libft.h"




typedef struct s_points
{
	double	x;
	double	y;
	double	z;
	int		color;
}				t_points;

typedef struct s_map
{
	int			width;
	int			height;
	t_points	***points;
}				t_map;

typedef struct s_mlx
{
	void	*mlx_p;
	void	*win_p;
	void	*img;
	char	*data;
	int		endian;
	int		bpp;
	int		sline;
	t_map	*map;

}				t_mlx;






#endif