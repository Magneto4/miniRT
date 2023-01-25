/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_elem2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngiroux <ngiroux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 19:38:59 by ngiroux           #+#    #+#             */
/*   Updated: 2023/01/25 14:31:31 by ngiroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	set_sphere(char **data, t_scene *scene)
{
	t_sphere	*sphere;

	if (check_sphere(data + 1) == false)
		return (false);
	sphere = malloc(sizeof(t_sphere));
	if (sphere == NULL)
		return (false);
	set_vector(data + 1, &sphere->pos);
	sphere->radius = __atod(data[2]) / 2;
	if (sphere->radius <= 0)
		return (free(sphere), true);
	set_rgb(data + 3, &sphere->rgb);
	__lstadd_front(&scene->sphere, __lstnew(sphere));
	return (true);
}

bool	set_plane(char **data, t_scene *scene)
{
	t_plane	*plane;

	if (check_plane(data + 1) == false)
		return (false);
	plane = malloc(sizeof(t_plane));
	if (plane == NULL)
		return (false);
	set_vector(data + 1, &plane->pos);
	set_vector(data + 2, &plane->dir);
	normalise(&plane->dir);
	set_rgb(data + 3, &plane->rgb);
	__lstadd_front(&scene->plane, __lstnew(plane));
	return (true);
}

void	set_def(t_cylinder *cylinder)
{
	t_vect	d;

	d = cylinder->dir;
	if (d.x != 0)
		cylinder->def = init_vector(-(d.y + d.z) / d.x, 1, 1);
	else if (d.y != 0)
		cylinder->def = init_vector(1, -(d.x + d.z) / d.y, 1);
	else if (d.z != 0)
		cylinder->def = init_vector(1, 1, -(d.x + d.y) / d.z);
	normalise(&(cylinder->def));
}

bool	set_cylinder(char **data, t_scene *scene)
{
	t_cylinder	*cylinder;

	if (check_cylinder(data + 1) == false)
		return (false);
	cylinder = malloc(sizeof(t_cylinder));
	if (cylinder == NULL)
		return (false);
	set_vector(data + 1, &cylinder->pos);
	set_vector(data + 2, &cylinder->dir);
	normalise(&cylinder->dir);
	cylinder->radius = __atod(data[3]) / 2;
	cylinder->height = __atod(data[4]);
	if (cylinder->radius <= 0 || cylinder->height <= 0)
		return (free(cylinder), true);
	cylinder->top = add(cylinder->pos, mult(cylinder->dir, cylinder->height));
	set_rgb(data + 5, &cylinder->rgb);
	__lstadd_front(&scene->cylinder, __lstnew(cylinder));
	set_def(cylinder);
	return (true);
}

bool	set_cone(char **data, t_scene *scene)
{
	t_cone	*cone;

	if (check_cylinder(data + 1) == false)
		return (false);
	cone = malloc(sizeof(t_cone));
	if (cone == NULL)
		return (false);
	set_vector(data + 1, &cone->pos);
	set_vector(data + 2, &cone->dir);
	normalise(&cone->dir);
	cone->radius = __atod(data[3]) / 2;
	cone->height = __atod(data[4]);
	if (cone->radius <= 0 || cone->height <= 0)
		return (free(cone), true);
	cone->top = add(cone->pos, mult(cone->dir, cone->height));
	set_rgb(data + 5, &cone->rgb);
	__lstadd_front(&scene->cone, __lstnew(cone));
	return (true);
}
