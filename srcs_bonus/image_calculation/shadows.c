/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadows.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseniak <nseniak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 15:49:09 by nseniak           #+#    #+#             */
/*   Updated: 2023/01/24 18:53:21 by nseniak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	shade_sphere(t_list *spheres, t_ray ray, double *t, void **inter)
{
	while (spheres)
	{
		sphere_shade(ray, (t_sphere *)(spheres->value), t, inter);
		spheres = spheres->next;
	}
}

void	shade_cylinder(t_minirt *minirt, t_ray ray, double *t, void **inter)
{
	t_point	point;

	point.init = 0;
	closest_cylinder(minirt, ray, &point);
	if (point.init && (*t < EPSILON || point.t < *t))
	{
		*t = point.t;
		*inter = point.shape;
	}
}

void	shade_cone(t_minirt *minirt, t_ray ray, double *t, void **inter)
{
	t_point	point;

	point.init = 0;
	closest_cone(minirt, ray, &point);
	if (point.init && (*t < EPSILON || point.t < *t))
	{
		*t = point.t;
		*inter = point.shape;
	}
}

int	shaded(t_minirt *minirt, t_ray ray, void *shape)
{
	double	t;
	void	*inter;

	t = -1;
	inter = NULL;
	shade_sphere(minirt->scene->sphere, ray, &t, &inter);
	shade_cylinder(minirt, ray, &t, &inter);
	shade_cone(minirt, ray, &t, &inter);
	shade_plane(minirt->scene->plane, ray, &t, &inter);
	if (t > EPSILON && inter != shape)
		return (1);
	return (0);
}
