#include "fdf.h"

int		error(char *str)
{
	ft_putendl(str);
	exit(1);
}

int		main(int ac, char **av)
{
	int		fd; 
	t_mlx	*mlx;
	t_map	*map;

	if (ac == 2)
	{
		if (!(mlx = (t_mlx*)malloc(sizeof(t_mlx))))
			error("ERROR: malloc error");
		fd = (argv[1], O_RDONLY);
		if (fd < 0)
			error("ERROR: ivalid input file!");
		map = validate(fd, av[1]);
			error("ERROR: while validating");
	}
	else
		return(error("usage: ./fdf [map], could be one file for reading"));
}

t_map	*validate(int fd, char *av)
{
	int		lines;
	char	*tmp;

	while()

}

int		lines_n_chars(char *av, int fd)
{
	int		chrs;
	int		lines;
	char	tmp;

	lines = 0;
	chrs = 0;
	while (read(fd, &tmp, 1))
	{
		if (tmp = '\n')
			lines++;
		if (!SPACE(tmp) && !ft_isdigit(temp))
			ft_putendl("ATTENTION: non-digit form in map!");
	}
}