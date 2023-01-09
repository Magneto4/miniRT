/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseniak <nseniak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 22:38:15 by nseniak           #+#    #+#             */
/*   Updated: 2023/01/06 19:45:51 by nseniak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	cylinder_inter(t_vect v, t_minirt *minirt, t_cylinder *cyl, t_point *closest)
{
	t_vect	tmp1;
	t_vect	tmp2;
	t_vect	quad;
	double	t[2];

	tmp1 = cross(cross(cyl->dir, v), cyl->dir);
	tmp2 = cross(cross(cyl->dir, sub(minirt->scene->cam.pos, cyl->pos)), cyl->dir);
	quad.x = dot(tmp1, tmp1);
	quad.y = 2 * dot(tmp2, tmp1);
	quad.z = dot(tmp2, tmp2) - cyl->radius * cyl->radius;
	if (solve_quadratic(quad, t, t + 1) == 0)
		return ;
	if (t[1] < 0)
		return ;
	if (t[0] < 0)
		t[0] = t[1];
	tmp1.x = minirt->scene->cam.pos.x + t[0] * v.x;
	tmp1.y = minirt->scene->cam.pos.y + t[0] * v.y;
	tmp1.z = minirt->scene->cam.pos.z + t[0] * v.z;
	if (closest->init && distance(tmp1, minirt->scene->cam.pos) > distance(closest->pos, minirt->scene->cam.pos))
		return ;
	closest->pos = tmp1;
	closest->raw_colour = cyl->rgb;
	closest->normal = cyl->dir;
	closest->init = 1;
	return ;
}

void	closest_cylinder(t_minirt *minirt, t_vect v, t_point *closest)
{
	t_list	*cylinders;

	cylinders = minirt->scene->cylinder;
	while (cylinders)
	{
		cylinder_inter(v, minirt, (t_cylinder *)(cylinders->value), closest);
		cylinders = cylinders->next;
	}
}
