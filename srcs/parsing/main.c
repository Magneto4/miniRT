#include "minirt.h"

int	put_error(char *str);
void	put_error_null(char *str);
bool	put_error_false(char *str);

int	main(int ac, char **av)
{
	t_minirt	*minirt;

	if (ac != 2)
		return (put_error("Usage: ./miniRT <file.rt>"));
	minirt = malloc(sizeof(t_minirt));
	if (!minirt)
		return (put_error("malloc failure"));
	minirt->scene = __parse(av[1]);
	if (!(minirt->scene))
		return (free(minirt), put_error("parse error"));
	write(1, "scene created\n", 14);

	t_sphere *sp = minirt->scene->sphere->value;

	printf("scene->sphere->radius: %f\n", sp->radius);
	printf("scene->sphere->pos->x: %f\n", sp->pos.x);
	printf("scene->sphere->pos->y: %f\n", sp->pos.y);
	printf("scene->sphere->pos->z: %f\n", sp->pos.z);	

	return (EXIT_SUCCESS);
}
