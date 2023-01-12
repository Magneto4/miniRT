/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_elem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngiroux <ngiroux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 13:04:04 by ngiroux           #+#    #+#             */
/*   Updated: 2023/01/12 18:02:33 by ngiroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// normalise and check null dir vector

void	set_ambiant(char **data, t_scene *scene)
{
	// if (check_ambiant(data + 1) == false)
	// 	return ;
	scene->al.ratio = __atod(data[1]);
	if (set_rgb(data + 2, &scene->al.rgb) == false)
		return ;
}

void	set_camera(char **data, t_scene *scene)
{
	set_vector(data + 1, &scene->cam.pos);
	set_vector(data + 2, &scene->cam.dir);
	normalise(&scene->cam.dir);
	scene->cam.fov = __atod(data[3]);
}

void	set_light(char **data, t_scene *scene)
{
	t_light	*light;

	light = malloc(sizeof(t_light));
	if (light == NULL)
		return ;
	set_vector(data + 1, &light->pos);
	light->ratio = __atod(data[2]);
	if (data[3] != NULL && BONUS == 1)
		set_rgb(data + 3, &light->rgb);
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
	set_vector(data + 1, &sphere->pos);
	sphere->radius = __atod(data[2]) / 2;
	if (sphere->radius <= 0)
		return (free(sphere));
	set_rgb(data + 3, &sphere->rgb);
	__lstadd_front(&scene->sphere, __lstnew(sphere));
}

void	set_plane(char **data, t_scene *scene)
{
	t_plane	*plane;

	plane = malloc(sizeof(t_plane));
	if (plane == NULL)
		return ;
	set_vector(data + 1, &plane->pos);
	set_vector(data + 2, &plane->dir);
	normalise(&plane->dir);
	set_rgb(data + 3, &plane->rgb);
	__lstadd_front(&scene->plane, __lstnew(plane));
}

void	set_cylinder(char **data, t_scene *scene)
{
	t_cylinder	*cylinder;

	cylinder = malloc(sizeof(t_cylinder));
	if (cylinder == NULL)
		return ;
	set_vector(data + 1, &cylinder->pos);
	set_vector(data + 2, &cylinder->dir);
	normalise(&cylinder->dir);
	cylinder->radius = __atod(data[3]) / 2;
	cylinder->height = __atod(data[4]);
	if (cylinder->radius <= 0 || cylinder->height <= 0)
		return (free(cylinder));
	set_rgb(data + 5, &cylinder->rgb);
	__lstadd_front(&scene->cylinder, __lstnew(cylinder));
}
