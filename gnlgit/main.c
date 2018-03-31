#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

int		main(int argc, char **argv)
{
	
	char *line;
	int	fd;

	
	fd = open(argv[1], O_RDONLY);
	int j = 0;
	while ((j = get_next_line(fd, &line)) > 0)
	{
		printf("(%d) %s\n", j, line);
		free(line);
	}
	printf("(%d) %s\n", j, line);
	close(fd);
	system("leaks -quiet a.out");
	return (0);

	/*fd = 42;
	int j = 0;

	j = get_next_line(fd, &line);
	printf("(%d) %s\n", j, line);
	free(line);
	close(fd);
	return (0);*/
}