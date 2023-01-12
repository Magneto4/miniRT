/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseniak <nseniak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 22:38:15 by nseniak           #+#    #+#             */
/*   Updated: 2023/01/12 23:52:06 by nseniak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vect	normal(t_vect p, t_cylinder *cyl)
{
	t_vect	tmp;
	t_vect	normal;

	tmp = sub(p, cyl->pos);
	normal = sub(tmp, mult(cyl->dir, dot(cyl->dir, tmp)));
	normalise(&normal);
	return (normal);
}

void	cylinder_inter(t_vect v, t_vect src, t_cylinder *cyl, t_point *closest)
{
	t_vect	r;
	t_vect	va;
	t_vect	quad;
	t_vect	tmp;
	t_vect	top;
	double	t[2];

	top = add(cyl->pos, mult(cyl->dir, cyl->height));
	r = cross(cyl->dir, sub(src, top));
	r = cross(r, cyl->dir);
	va = cross(cyl->dir, v);
	va = cross(va, cyl->dir);
	quad.x = dot(va, va);
	quad.y = 2 * dot(r, va);
	quad.z = dot(r, r) - cyl->radius * cyl->radius;
	if (solve_quadratic(quad, t, t + 1) == 0)
		return ;
	if (t[1] < 0)
		return ;
	if (t[0] < 0)
		t[0] = t[1];
	tmp = add(src, mult(v, t[0]));
	if (dot(sub(tmp, cyl->pos), cyl->dir) <= 0)
		return ;
	if (dot(sub(tmp, top), cyl->dir) >= 0)
		return ;
	if (closest->init && distance(tmp, src) > distance(closest->pos, src))
		return ;
	closest->pos = tmp;
	closest->raw_colour = cyl->rgb;
	closest->normal = normal(tmp, cyl);
	closest->shape = cyl;
	closest->init = 1;
	return ;
}

void	closest_cylinder(t_minirt *minirt, t_ray ray, t_point *closest)
{
	t_list	*cylinders;

	cylinders = minirt->scene->cylinder;
	while (cylinders)
	{
		cylinder_inter(ray.dir, ray.src, (t_cylinder *)(cylinders->value), closest);
		cylinders = cylinders->next;
	}
}
