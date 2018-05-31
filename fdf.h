#ifndef FDF_H
# define FDF_H

# define W_HGHT 1200
# define W_WID  1200
# define DIST	30
# define SPACE(x) (x == ' ' || x == '\t' || x == '\n') 

#include <mlx.h>
#include <fcntl.h>
#include "libft/libft.h"
#include <math.h>



typedef struct s_points
{
	float	x;
	float	y;
	float	z;
	int		color;
}				t_points;

typedef struct s_map
{
	int			width;
	int			height;
	int			z_min;
	int			z_max;
	double		scale;
	t_points	**points;
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
	int		img_color;
	t_map	*map;

}				t_mlx;


 typedef struct	s_brez
 {
	int			dy;
	int			dx;
	int			sig_x;
	int			sig_y;
	int			err;
	int			err2;
 }				t_brez;

/////////////////////////////////////////////////////////////////////////////////
// typedef struct		s_line
// {
// 	t_vector	start;
// 	t_vector	stop;
// 	int			dx;
// 	int			dy;
// 	int			sx;
// 	int			sy;
// 	int			err;
// 	int			err2;
// }					t_line;



/////////////////////////////////////////////////////////////////////////////////

int				error(char *str);
t_points		rotate(t_points p);
int				first_line_width(char *tmp);
t_map			*find_z(t_map *m);
t_points		*make_points(char *tmp, int l, t_map *map);
int				lines_n_chars(char *av, t_map **map, int chrs, int lines, int f_line);
t_map			*validate(char **av, int fd);
t_mlx			*mlx_make(char *av, t_map *map);
int				hook_keydown(int key, t_mlx *mlx);
t_mlx			*clean_mlx(t_mlx *mlx);
t_points		center(t_points a, t_mlx *mlx);
t_points		scale_mat(t_points p, t_mlx *mlx);
int				lines_nb(char *av, t_map **map, int lines);
void			points(t_points a1, t_points a2, t_mlx *mlx);


// DELETE!!!!!!!!!
void			ft_draw(t_mlx *mlx);
int				exit_x(void *par);
int				draw_l(int xs, int ys, int xe, int ye, t_mlx *mlx);


#endif