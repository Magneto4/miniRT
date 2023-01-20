/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_elem2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseniak <nseniak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 19:38:59 by ngiroux           #+#    #+#             */
/*   Updated: 2023/01/20 15:32:52 by nseniak          ###   ########.fr       */
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
	__lstadd_front(&scene->cylinder, __lstnew(cylinder));zz
	return (true);
}
