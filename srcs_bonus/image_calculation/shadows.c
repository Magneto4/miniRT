/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadows.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseniak <nseniak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 15:49:09 by nseniak           #+#    #+#             */
/*   Updated: 2023/01/18 18:34:36 by nseniak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void shade_plane(t_list *planes, t_ray ray, double *t, void **inter)
{
	t_plane	*plane;
	double	a;

	while (planes)
	{
		plane = (t_plane *)(planes->value);
		a = -1 * dot(plane->dir, sub(ray.src, plane->pos));
		a /= dot(plane->dir, ray.dir);
		if (*t < 0 || (a > EPSILON && a < *t))
		{
			*t = a;
			*inter = plane;
		}
		planes = planes->next;
	}
}

void	sphere_shade(t_ray ray, t_sphere *sphere, double *t, void **inter)
{
	double	x[2];
	t_vect	tmp;
	t_vect	quad;

	tmp = sub(ray.src, sphere->pos);
	quad.x = 1;
	quad.y = dot(ray.dir, tmp) * 2;
	quad.z = dot(tmp, tmp) - sphere->radius * sphere->radius;
	if (solve_quadratic(quad, x, x + 1) == 0)
		return ;
	if (x[1] < EPSILON)
		return ;
	if (x[0] < EPSILON)
		x[0] = x[1];
	if (*t > 0 && x[0] > *t)
		return ;
	*t = x[0];
	*inter = sphere;
}

void shade_sphere(t_list *spheres, t_ray ray, double *t, void **inter)
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

int	shaded(t_minirt *minirt, t_ray ray, void *shape)
{
	double	t;
	void	*inter;

	t = -1;
	inter = NULL;
	shade_sphere(minirt->scene->sphere, ray, &t, &inter);
	shade_cylinder(minirt, ray, &t, &inter);
	shade_plane(minirt->scene->plane, ray, &t, &inter);
	if (t > EPSILON && inter != shape)
		return (1);
	return (0);
}
