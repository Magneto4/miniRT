/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngiroux <ngiroux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 22:38:15 by nseniak           #+#    #+#             */
/*   Updated: 2023/01/14 19:48:07 by ngiroux          ###   ########.fr       */
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

int	in_cyl(float t, t_cylinder *cyl, t_ray ray)
{
	t_vect	inter;
	t_vect	top;

	inter = add(ray.src, mult(ray.dir, t));
	if (dot(sub(inter, cyl->pos), cyl->dir) <= 0)
		return (0);
	top = add(cyl->pos, mult(cyl->dir, cyl->height));
	if (dot(sub(inter, top), cyl->dir) >= 0)
		return (0);
	return (1);
}

void	cylinder_inter(t_ray ray, t_cylinder *cyl, t_point *closest)
{
	t_vect	r;
	t_vect	va;
	t_vect	tmp;
	double	t[2];

	r = cross(cyl->dir, sub(ray.src, cyl->pos));
	r = cross(r, cyl->dir);
	va = cross(cyl->dir, ray.dir);
	va = cross(va, cyl->dir);
	tmp.x = dot(va, va);
	tmp.y = 2. * dot(r, va);
	tmp.z = dot(r, r) - cyl->radius * cyl->radius;
	if (solve_quadratic(tmp, t, t + 1) == 0)
		return ;
	if (t[1] < EPSILON)
		return ;
	// printf("x1 %f x2 %f\n", t[0], t[1]);
	if (t[0] < EPSILON)
	{
		t[0] = t[1];
		if (!in_cyl(t[0], cyl, ray))
			return ;
		if (closest->init && t[0] >= closest->t)
		{
			return ;
		}
	}
	else
	{
		if (!in_cyl(t[0], cyl, ray))
		{
			if (!in_cyl(t[1], cyl, ray))
				return ;
			else
				t[0] = t[1];
		}
		// printf("t[0] %f, t %f\n", t[0], closest->t);
		if (closest->init && t[0] >= closest->t)
			return ;
	}
	closest->t = t[0];
	closest->pos = add(ray.src, mult(ray.dir, t[0]));
	closest->raw_colour = cyl->rgb;
	closest->normal = normal(closest->pos, cyl);
	closest->shape = cyl;
	closest->init = CY;
	return ;
}

void	caps_inter(t_ray ray, t_cylinder *cyl, t_point *closest)
{
	t_plane	plane;
	t_point	point;

	point.init = 0;
	plane.dir = cyl->dir;
	plane.pos = cyl->pos;
	plane.rgb = cyl->rgb;
	plane_inter(ray, &plane, &point);
	if (point.init && distance(plane.pos, point.pos) > cyl->radius)
		point.init = 0;
	plane.pos = add(cyl->pos, mult(cyl->dir, cyl->height));
	plane_inter(ray, &plane, &point);
	if (point.init && distance(plane.pos, point.pos) > cyl->radius)
		point.init = 0;
	if (point.init == 0)
		return ;
	if (closest->init && point.t > closest->t)
		return ;
	closest->t = point.t;
	closest->init = CY;
	closest->pos = point.pos;
	closest->normal = plane_normal(&plane, ray.src, closest->pos);
	closest->raw_colour = cyl->rgb;
	closest->shape = cyl;
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
