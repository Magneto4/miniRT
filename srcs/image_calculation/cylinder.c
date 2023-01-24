/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseniak <nseniak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 22:38:15 by nseniak           #+#    #+#             */
/*   Updated: 2023/01/24 16:33:49 by nseniak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
