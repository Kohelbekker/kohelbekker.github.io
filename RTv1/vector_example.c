#include <stdio.h>

/*typedef double t_vector __attribute__((vector_size(8*3)));

void		print(t_vector a)
{
	printf("{ %lf, %lf, %lf }\n", a[0], a[1], a[2]);
}

int		main(void)
{
	t_vector a;
	t_vector b;
	t_vector c;

	b = (t_vector){5.0, 5.0, 7.0};
	a = (t_vector){1.0, 6.0, 3.0};
	print(a);
	print(b);
	c = a > b;
	print(c);
	c = a * b;
	print(c);
}*/

typedef int t_vector __attribute__ ((vector_size (3 * sizeof(int))));


void		print(t_vector a)
{
	printf("{ %d, %d, %d }\n", a[0], a[1], a[2]);
}

int		main(void)
{
	t_vector a, b, c, d;
	int g = 5;
	long l;

	d = (t_vector){g, g, g};
	b = (t_vector){5, 10, -5};
	a = d + g;
	print(a);
	a = (t_vector){2, 2, 2} * b;
	print(a);
	return (0);
}