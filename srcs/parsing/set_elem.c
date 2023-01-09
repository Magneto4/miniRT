/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_elem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngiroux <ngiroux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 13:04:04 by ngiroux           #+#    #+#             */
/*   Updated: 2023/01/09 14:51:02 by ngiroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	set_ambiant(char **data, t_scene *scene)
{
	scene->al.ratio = __atod(data[0]);
	set_rgb(data + 1, &scene->al.rgb);
}

void	set_camera(char **data, t_scene *scene)
{
	set_vector(data, &scene->cam.pos);
	set_vector(data + 3, &scene->cam.dir);
	scene->cam.fov = __atod(data[6]);
}

void	set_light(char **data, t_scene *scene)
{
	t_light	*light;

	light = malloc(sizeof(t_light));
	if (light == NULL)
		return ;
	set_vector(data, &light->pos);
	light->ratio = __atod(data[3]);
	if (data[4] != NULL)
		set_rgb(data + 4, &light->rgb);
	else
		light->rgb = (t_rgb){255, 255, 255};
	__lstadd_front(&scene->lights, __lstnew(light));
}

void	set_sphere(char **data, t_scene *scene)
{
	t_sphere	*sphere;

	sphere = malloc(sizeof(t_sphere));
	if (sphere == NULL)
		return ;
	set_vector(data, &sphere->pos);
	sphere->radius = __atod(data[3]);
	set_rgb(data + 4, &sphere->rgb);
	__lstadd_front(&scene->sphere, __lstnew(sphere));
}

void	set_plane(char **data, t_scene *scene)
{
	t_plane	*plane;

	plane = malloc(sizeof(t_plane));
	if (plane == NULL)
		return ;
	set_vector(data, &plane->pos);
	set_vector(data + 3, &plane->dir);
	set_rgb(data + 6, &plane->rgb);
	__lstadd_front(&scene->plane, __lstnew(plane));
}

void	set_cylinder(char **data, t_scene *scene)
{
	t_cylinder	*cylinder;

	cylinder = malloc(sizeof(t_cylinder));
	if (cylinder == NULL)
		return ;
	set_vector(data, &cylinder->pos);
	set_vector(data + 3, &cylinder->dir);
	cylinder->radius = __atod(data[6]);
	cylinder->height = __atod(data[7]);
	set_rgb(data + 8, &cylinder->rgb);
	__lstadd_front(&scene->cylinder, __lstnew(cylinder));
}

