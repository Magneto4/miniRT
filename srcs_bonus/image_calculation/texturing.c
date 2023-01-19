/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texturing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseniak <nseniak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 15:39:19 by nseniak           #+#    #+#             */
/*   Updated: 2023/01/19 18:08:33 by nseniak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vect2	sphere_coord(t_point *point, t_sphere *sphere)
{
	t_vect2	coord;
	t_vect	d;

	d = sub(point->pos, sphere->pos);
	coord.u = 0.5 + atan2(d.z, d.x) / 2 / M_PI;
	coord.v = 0.5 - asin(d.y / sphere->radius) / M_PI;
	coord.u = fmod(coord.u * 2, 1.);
	if (coord.u < 0)
		coord.u += 1.;
	return (coord);
}

t_vect2	plane_coord(t_point *point)
{
	t_vect	uax;
	t_vect	vax;
	t_vect2	coord;

	uax = init_vector(point->normal.y, point->normal.z, -1 * point->normal.x);
	vax = cross(uax, point->normal);
	coord.u = fmod(dot(point->pos, uax), 1.);
	if (coord.u < 0)
		coord.u += 1;
	coord.v = fmod(dot(point->pos, vax), 1.);
	if (coord.v < 0)
		coord.v += 1;
	return(coord);
}

t_vect2	cylinder_coord(t_point *point, t_cylinder *cyl)
{
	t_vect2	coord;

	if (point->init == CY_C)
		return (plane_coord(point));
	coord.u = atan2(point->pos.y, point->pos.x) / 2 / M_PI;
	coord.v = point->pos.z / cyl->height;
	(void)cyl;
	return(coord);
}

t_vect2	flat_coord(t_point *point)
{
	t_vect2	coord;

	if (point->init == SP)
		coord = sphere_coord(point, (t_sphere *)point->shape);
	if (point->init == PL)
		coord = plane_coord(point);
	if (point->init == CY || point->init == CY_C)
		coord = cylinder_coord(point, (t_cylinder *)point->shape);
	return (coord);
}

void	checkering(t_point *point, t_vect2 coord)
{
	int	n;
	int	m;

	n = 1;
	while (n <= 10)
	{
		m = 1;
		while (m <= 10)
		{
			if (coord.u <= n * 0.1 && coord.v <= m * 0.1)
			{
				if ((n + m) % 2)
					point->rgb = int_to_rgb(0x000000);
				else
					point->rgb = int_to_rgb(0xffffff);
				return ;
			}
			m ++;
		}
		n ++;
	}
}

void	texturing(t_point *point)
{
	t_vect2	coord;

	if (!(point->checkered))
		return ;
	coord = flat_coord(point);
	checkering(point, coord);
}
