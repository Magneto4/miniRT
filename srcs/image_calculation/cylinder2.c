/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseniak <nseniak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 16:33:34 by nseniak           #+#    #+#             */
/*   Updated: 2023/02/09 14:04:01 by nseniak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vect	normal_cylinder(t_vect p, t_cylinder *cyl, t_vect src)
{
	t_vect	tmp;
	t_vect	normal;

	tmp = sub(p, cyl->pos);
	normal = sub(tmp, mult(cyl->dir, dot(cyl->dir, tmp)));
	if (norm(cross(sub(src, cyl->pos), cyl->dir)) <= cyl->radius)
		normal = mult(normal, -1);
	normalise(&normal);
	return (normal);
}

int	in_cyl(t_cylinder *cyl, t_vect pos)
{
	if (dot(sub(pos, cyl->pos), cyl->dir) < 0)
		return (0);
	if (dot(sub(pos, cyl->top), cyl->dir) > 0)
		return (0);
	return (1);
}

int	best_t(double *t, t_ray ray, t_cylinder *cyl)
{
	if (t[1] < EPSILON)
		return (1);
	if (t[0] < EPSILON)
	{
		t[0] = t[1];
		if (!in_cyl(cyl, add(ray.src, mult(ray.dir, t[0]))))
			return (1);
	}
	else
	{
		if (!in_cyl(cyl, add(ray.src, mult(ray.dir, t[0]))))
		{
			if (!in_cyl(cyl, add(ray.src, mult(ray.dir, t[1]))))
				return (1);
			else
				t[0] = t[1];
		}
	}
	return (0);
}

void	cylinder_inter(t_ray ray, t_cylinder *cyl, t_point *closest)
{
	t_vect	r;
	t_vect	va;
	t_vect	tmp;
	double	t[2];

	r = cross(cross(cyl->dir, sub(ray.src, cyl->pos)), cyl->dir);
	va = cross(cross(cyl->dir, ray.dir), cyl->dir);
	tmp.x = dot(va, va);
	tmp.y = 2. * dot(va, r);
	tmp.z = dot(r, r) - cyl->radius * cyl->radius;
	if (solve_quadratic(tmp, t, t + 1) == 0)
		return ;
	if (best_t(t, ray, cyl))
		return ;
	if (closest->init && t[0] >= closest->t)
		return ;
	closest->t = t[0];
	closest->pos = add(ray.src, mult(ray.dir, t[0]));
	closest->rgb = cyl->rgb;
	closest->normal = normal_cylinder(closest->pos, cyl, ray.src);
	closest->shape = cyl;
	closest->init = CY;
	return ;
}
