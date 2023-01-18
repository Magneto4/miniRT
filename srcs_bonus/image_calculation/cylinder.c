/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseniak <nseniak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 22:38:15 by nseniak           #+#    #+#             */
/*   Updated: 2023/01/17 23:34:45 by nseniak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vect	normal(t_vect p, t_cylinder *cyl, t_vect src)
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
	closest->normal = normal(closest->pos, cyl, ray.src);
	closest->shape = cyl;
	closest->init = CY;
	return ;
}

t_point	cap(t_ray ray, t_cylinder *cyl, t_vect pos)
{
	t_point	point;
	t_plane	plane;

	point.init = 0;
	plane.dir = cyl->dir;
	plane.pos = pos;
	plane.rgb = cyl->rgb;
	plane_inter(ray, &plane, &point);
	if (point.init && distance(plane.pos, point.pos) > cyl->radius)
		point.init = 0;
	return (point);
}

t_point	which_closest(t_point p1, t_point p2)
{
	if (!(p1.init) && !(p2.init))
		return (p1);
	if ((p1.init) && !(p2.init))
		return (p1);
	if (!(p1.init) && (p2.init))
		return (p2);
	else
	{
		if (p1.t < p2.t)
			return (p1);
		else
			return (p2);
	}
}

void	caps_inter(t_ray ray, t_cylinder *cyl, t_point *closest)
{
	t_point	point1;
	t_point	point2;

	point1 = cap(ray, cyl, cyl->pos);
	point2 = cap(ray, cyl, add(cyl->pos, mult(cyl->dir, cyl->height)));
	point1 = which_closest(point1, point2);
	if (point1.init)
	{
		if (closest->init == 0 || closest->t > point1.t)
		{
			closest->t = point1.t;
			closest->pos = point1.pos;
			closest->normal = point1.normal;
			closest->init = CY;
			closest->rgb = cyl->rgb;
			closest->shape = cyl;
		}
	}
}

void	closest_cylinder(t_minirt *minirt, t_ray ray, t_point *closest)
{
	t_list	*cylinders;

	cylinders = minirt->scene->cylinder;
	while (cylinders)
	{
		cylinder_inter(ray, (t_cylinder *)(cylinders->value), closest);
		caps_inter(ray, (t_cylinder *)(cylinders->value), closest);
		cylinders = cylinders->next;
	}
}
