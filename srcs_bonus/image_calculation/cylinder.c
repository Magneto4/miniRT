/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseniak <nseniak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 22:38:15 by nseniak           #+#    #+#             */
/*   Updated: 2023/01/25 20:34:19 by nseniak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
	closest->bonus = cyl->bonus;
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

int	which_closest(t_point p1, t_point p2)
{
	if (!(p1.init) && !(p2.init))
		return (1);
	if ((p1.init) && !(p2.init))
		return (1);
	if (!(p1.init) && (p2.init))
		return (2);
	else
	{
		if (p1.t < p2.t)
			return (1);
		else
			return (2);
	}
}

void	caps_inter(t_ray ray, t_cylinder *cyl, t_point *closest)
{
	t_point	point1;
	t_point	point2;
	int		which;

	point1 = cap(ray, cyl, cyl->pos);
	point2 = cap(ray, cyl, add(cyl->pos, mult(cyl->dir, cyl->height)));
	which = which_closest(point1, point2);
	if (which == 2)
		point1 = point2;
	if (point1.init)
	{
		if (closest->init == 0 || closest->t > point1.t)
		{
			closest->t = point1.t;
			closest->pos = point1.pos;
			closest->normal = point1.normal;
			closest->init = CY_B * (which == 1) + CY_T * (which == 2);
			closest->rgb = cyl->rgb;
			closest->shape = cyl;
			closest->bonus = cyl->bonus;
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
