/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_mapping.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseniak <nseniak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 12:17:00 by nseniak           #+#    #+#             */
/*   Updated: 2023/01/30 13:23:44 by nseniak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vect	tangent_sphere(t_point *point)
{
	t_vect	t;

	t = init_vector(-1 * point->normal.x / point->normal.z, 0, 1);
	normalise(&t);
	return (t);
}

t_vect	tangent_plane(t_point *point)
{
	t_vect	t;

	t = init_vector(point->normal.y, point->normal.z, -1 * point->normal.x);
	normalise(&t);
	return (t);
}

t_vect	tangent_cylinder(t_point *point)
{
	t_vect		b;
	t_vect		t;
	t_vect		pos;
	t_cylinder	*cyl;

	cyl = (t_cylinder *)(point->shape);
	if (point->init == CY_T || point->init == CY_B)
	{
		if (point->init == CY_T)
			pos = cyl->top;
		else
			pos = cyl->pos;
		b = sub(point->pos, pos);
		t = cross(b, point->normal);
	}
	else
		t = cross(cyl->def, point->normal);
	normalise(&t);
	return (t);
}


void	normal_mapping(t_point *point, t_vect2 coord)
{
	t_vect	t;
	t_vect	b;
	t_mat	mat;

	if (point->init == SP)
		t = tangent_sphere(point);
	else if (point->init == PL)
		t = tangent_plane(point);
	else if (point->init == CY || point->init == CY_T || point->init == CY_B)
		t = tangent_cylinder(point);
	b = cross(point->normal, t);
	normalise(&b);
	mat[0][0] = t.x;
	mat[1][0] = t.y;
	mat[2][0] = t.z;
	mat[0][1] = b.x;
	mat[1][1] = b.y;
	mat[2][1] = b.z;
	mat[0][2] = point->normal.x;
	mat[1][2] = point->normal.y;
	mat[2][2] = point->normal.z;
	//replace with proper vector
	(void)coord;
	point->normal = mat_mult(mat, init_vector(0, 0, 1));
}
