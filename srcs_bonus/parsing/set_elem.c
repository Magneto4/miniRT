/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_elem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseniak <nseniak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 13:04:04 by ngiroux           #+#    #+#             */
/*   Updated: 2023/01/19 14:15:29 by nseniak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	set_ambiant(char **data, t_scene *scene)
{
	if (check_ambiant(data + 1) == false)
		return (false);
	scene->al.ratio = __atod(data[1]);
	set_rgb(data + 2, &scene->al.rgb);
	return (true);
}

bool	set_camera(char **data, t_scene *scene)
{
	if (check_camera(data + 1) == false)
		return (false);
	set_vector(data + 1, &scene->cam.pos);
	set_vector(data + 2, &scene->cam.dir);
	normalise(&scene->cam.dir);
	scene->cam.fov = __atod(data[3]);
	return (true);
}

bool	set_light(char **data, t_scene *scene)
{
	t_light	*light;

	if (scene->lights != NULL && BONUS == 0)
		return (put_error_false("light already set"));
	if (check_light(data + 1) == false)
		return (false);
	light = malloc(sizeof(t_light));
	if (light == NULL)
		return (false);
	set_vector(data + 1, &light->pos);
	light->ratio = __atod(data[2]);
	if (data[3] != NULL && BONUS == 1)
		set_rgb(data + 3, &light->rgb);
	else
		light->rgb = (t_rgb){255, 255, 255};
	__lstadd_front(&scene->lights, __lstnew(light));
	return (true);
}
