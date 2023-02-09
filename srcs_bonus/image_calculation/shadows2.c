/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadows2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseniak <nseniak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 18:53:13 by nseniak           #+#    #+#             */
/*   Updated: 2023/02/09 17:22:36 by nseniak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	shade_plane(t_list *planes, t_ray ray, double *t, void **inter)
{
	t_plane	*plane;
	double	a;

	while (planes)
	{
		plane = (t_plane *)(planes->value);
		a = -1 * dot(plane->dir, sub(ray.src, plane->pos));
		a /= dot(plane->dir, ray.dir);
		if (*t < 0 || (a > EPSILON && a - EPSILON < *t))
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
	if (*t > 0 && x[0] > *t + EPSILON)
		return ;
	*t = x[0];
	*inter = sphere;
}
