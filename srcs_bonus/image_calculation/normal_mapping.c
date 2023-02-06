/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_mapping.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseniak <nseniak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 12:17:00 by nseniak           #+#    #+#             */
/*   Updated: 2023/02/06 16:52:47 by nseniak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	tangent_sphere(t_point *point, t_vect *bt)
{
	bt[1] = cross(init_vector(0, 1, 0), point->normal);
	bt[0] = cross(point->normal, bt[1]);
	normalise(bt);
	normalise(bt + 1);
}

void	tangent_plane(t_point *point, t_vect *bt)
{
	bt[0] = init_vector(point->normal.y, point->normal.z, -1 * point->normal.x);
	bt[1] = cross(bt[0], point->normal);
	normalise(bt);
	normalise(bt + 1);
}

void	tangent_cylinder(t_point *point, t_vect *bt)
{
	t_cylinder	*cyl;

	cyl = (t_cylinder *)(point->shape);
	if (point->init == CY_T || point->init == CY_B)
		bt[1] = cross(cyl->def, point->normal);
	else
		bt[1] = cross(cyl->dir, point->normal);
	bt[0] = cross(bt[1], point->normal);
	normalise(bt);
	normalise(bt + 1);
}

void	normal_mapping(t_point *point, t_vect2 coord)
{
	t_vect	bt[2];
	t_mat	mat;
	t_vect	new_norm;

	if (point->init == SP)
		tangent_sphere(point, bt);
	else if (point->init == PL)
		tangent_plane(point, bt);
	else if (point->init == CY || point->init == CY_T || point->init == CY_B)
		tangent_cylinder(point, bt);
	mat[0][0] = bt[1].x;
	mat[1][0] = bt[1].y;
	mat[2][0] = bt[1].z;
	mat[0][1] = bt[0].x;
	mat[1][1] = bt[0].y;
	mat[2][1] = bt[0].z;
	mat[0][2] = point->normal.x;
	mat[1][2] = point->normal.y;
	mat[2][2] = point->normal.z;
	new_norm = get_normal2(*point, (int)(coord.u * \
	point->bonus.text.width), (int)(coord.v * point->bonus.text.height));
	point->normal = mat_mult(mat, new_norm);
	normalise(&(point->normal));
}
