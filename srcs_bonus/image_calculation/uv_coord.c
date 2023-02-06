/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uv_coord.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseniak <nseniak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 12:14:30 by nseniak           #+#    #+#             */
/*   Updated: 2023/02/06 16:53:01 by nseniak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vect2	sphere_coord(t_point *point, t_sphere *sphere)
{
	t_vect2	coord;
	t_vect	d;

	d = sub(point->pos, sphere->pos);
	coord.u = 0.5 + atan2(d.z, d.x) / (2 * M_PI);
	coord.v = 0.5 - asin(d.y / sphere->radius) / M_PI;
	return (coord);
}

t_vect2	plane_coord(t_point *point)
{
	t_vect	uax;
	t_vect	vax;
	t_vect2	coord;

	vax = init_vector(point->normal.y, point->normal.z, -1 * point->normal.x);
	uax = cross(vax, point->normal);
	coord.u = fmod(dot(point->pos, uax) / 2, 1.);
	if (coord.u < 0)
		coord.u += 1;
	coord.v = fmod(dot(point->pos, vax) / 2, 1.);
	if (coord.v < 0)
		coord.v += 1;
	return (coord);
}

t_vect2	cylinder_coord_caps(t_point *point, t_cylinder *cyl)
{
	t_vect2	coord;
	double	angle;
	t_vect	v;
	t_vect	pos;

	if (point->init == CY_B)
		pos = cyl->pos;
	if (point->init == CY_T)
		pos = cyl->top;
	v = sub(point->pos, pos);
	normalise(&v);
	angle = acos(dot(cyl->def, v));
	coord.v = distance(point->pos, pos) / cyl->radius / 2;
	if (dot(cross(cyl->dir, cyl->def), v) < 0)
		angle = angle * -1;
	coord.u = fmod(angle / (M_PI), 1.);
	coord.u += 1.;
	coord.u /= 2.;
	return (coord);
}

t_vect2	cylinder_coord(t_point *point, t_cylinder *cyl)
{
	t_vect2	coord;
	double	angle;
	t_vect	v;

	if (point->init != CY)
		return (cylinder_coord_caps(point, cyl));
	angle = acos(dot(cyl->def, point->normal));
	v = sub(point->pos, cyl->pos);
	coord.v = 1 - sqrt(dot(v, v) - cyl->radius * cyl->radius) / cyl->height;
	if (dot(cross(cyl->dir, cyl->def), v) < 0)
		angle = angle * -1;
	coord.u = fmod(angle / (M_PI), 1.);
	coord.u += 1.;
	coord.u /= 2.;
	coord.u = 1 - coord.u;
	return (coord);
}

t_vect2	flat_coord(t_point *point)
{
	t_vect2	coord;

	if (point->init == SP)
		coord = sphere_coord(point, (t_sphere *)point->shape);
	if (point->init == PL)
		coord = plane_coord(point);
	if (point->init == CY || point->init == CY_T || point->init == CY_B)
		coord = cylinder_coord(point, (t_cylinder *)point->shape);
	return (coord);
}
