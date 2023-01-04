/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_minirt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseniak <nseniak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 16:25:18 by nseniak           #+#    #+#             */
/*   Updated: 2023/01/04 16:32:12 by nseniak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	del_cyl(void *void_cyl)
{
	t_cylinder	*cyl;

	cyl = (t_cylinder *)void_cyl;
	free (cyl);
}

void	del_lights(void *void_light)
{
	t_light	*light;

	light = (t_light *)void_light;
	free (light);
}

void	del_sphere(void *void_sphere)
{
	t_sphere	*sphere;

	sphere = (t_sphere *)void_sphere;
	free (sphere);
}

void	del_plane(void *void_plane)
{
	t_plane	*plane;

	plane = (t_plane *)void_plane;
	free (plane);
}

void	free_minirt(t_minirt *minirt)
{
	free(minirt->mlx->mlx_ptr);
	free(minirt->mlx);
	free(minirt->scene->cam->dir);
	free(minirt->scene->cam->pos);
	free(minirt->scene->cam);
	if (minirt->scene->cylinder)
		__lstclear(&(minirt->scene->cylinder), del_cyl);
	if (minirt->scene->lights)
		__lstclear(&(minirt->scene->lights), del_lights);
	if (minirt->scene->plane)
		__lstclear(&(minirt->scene->plane), del_plane);
	if (minirt->scene->sphere)
		__lstclear(&(minirt->scene->sphere), del_sphere);
	free(minirt->scene);
	free(minirt);
}
