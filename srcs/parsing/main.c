#include "minirt.h"

static void	print_rgb(t_rgb rgb)
{
	printf("rgb: %d, %d, %d\n", rgb.r, rgb.g, rgb.b);
}

static void	print_vect(t_vect vect)
{
	printf("vect: %f, %f, %f\n", vect.x, vect.y, vect.z);
}

static void	print_ambiant(t_ambiant al)
{
	if (al.ratio < 0)
		return (put_error_null("Error ambiant light"));
	printf("Ambiant light:\n");
	print_rgb(al.rgb);
	printf("ratio: %f\n", al.ratio);
	write(1, "\n", 1);
}

static void	print_camera(t_camera cam)
{
	if (cam.fov < 0)
		return (put_error_null("Error camera"));
	printf("Camera:\n");
	print_vect(cam.pos);
	print_vect(cam.dir);
	printf("fov: %f\n", cam.fov);
	write(1, "\n", 1);
}

static void	print_light(t_light *light)
{
	if (!light)
		return (put_error_null("Error light"));
	printf("Light:\n");
	print_vect(light->pos);
	print_rgb(light->rgb);
	printf("ratio: %f\n", light->ratio);
	write(1, "\n", 1);
}

static void	print_sphere(t_sphere *sphere)
{
	if (!sphere)
		return (put_error_null("Error sphere"));
	printf("Sphere:\n");
	print_vect(sphere->pos);
	printf("radius: %f\n", sphere->radius);
	print_rgb(sphere->rgb);
	write(1, "\n", 1);
}

static void	print_plane(t_plane *plane)
{
	if (!plane)
		return (put_error_null("Error plane"));
	printf("Plane:\n");
	print_vect(plane->pos);
	print_vect(plane->dir);
	print_rgb(plane->rgb);
	write(1, "\n", 1);
}

static void	print_cylinder(t_cylinder *cylinder)
{
	if (!cylinder)
		return (put_error_null("Error cylinder"));
	printf("Cylinder:\n");
	print_vect(cylinder->pos);
	print_vect(cylinder->dir);
	printf("radius: %f\n", cylinder->radius);
	printf("height: %f\n", cylinder->height);
	print_rgb(cylinder->rgb);
	write(1, "\n", 1);
}

static void	print_scene(t_scene *scene)
{
	t_list	*tmp;

	print_ambiant(scene->al);
	print_camera(scene->cam);
	tmp = scene->lights;
	while (tmp)
	{
		print_light((t_light *)(tmp->value));
		tmp = tmp->next;
	}
	tmp = scene->sphere;
	while (tmp)
	{
		print_sphere((t_sphere *)(tmp->value));
		tmp = tmp->next;
	}
	tmp = scene->plane;
	while (tmp)
	{
		print_plane((t_plane *)(tmp->value));
		tmp = tmp->next;
	}
	tmp = scene->cylinder;
	while (tmp)
	{
		print_cylinder((t_cylinder *)(tmp->value));
		tmp = tmp->next;
	}
}

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
	print_scene(minirt->scene);
	free_scene(minirt->scene);
	free(minirt->scene);
	free(minirt);
	return (EXIT_SUCCESS);
}
