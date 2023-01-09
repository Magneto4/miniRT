/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseniak <nseniak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 22:38:15 by nseniak           #+#    #+#             */
/*   Updated: 2023/01/09 15:01:53 by nseniak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vect	normal(t_vect p, t_cylinder *cyl)
{
	t_vect	n;
	t_vect	v;
	double	t;
	double	angle;

	angle = asin(cyl->radius / norm(sub(p, cyl->pos)));
	t = cyl->radius / tan(angle);
	v = add(cyl->pos, mult(cyl->dir, t));
	n = sub(p, v);
	normalise(&n);
	return (n);
}

void	cylinder_inter(t_vect v, t_minirt *minirt, t_cylinder *cyl, t_point *closest)
{
	t_vect	r;
	t_vect	va;
	t_vect	quad;
	t_vect	tmp;
	t_vect	extrem[2];
	double	t[2];

	extrem[0] = sub(cyl->pos, mult(cyl->dir, cyl->height / 2));
	extrem[1] = add(cyl->pos, mult(cyl->dir, cyl->height / 2));
	r = cross(cyl->dir, sub(minirt->scene->cam.pos, extrem[1]));
	r = cross(r, cyl->dir);
	va = cross(cyl->dir, v);
	va = cross(va, cyl->dir);
	quad.x = dot(va, va);
	quad.y = 2 * dot(r, va);
	quad.z = dot(r, r) - cyl->radius * cyl->radius;
	if (solve_quadratic(quad, t, t + 1) == 0)
		return ;
	if (t[1] < 0)
		return ;
	if (t[0] < 0)
		t[0] = t[1];
	tmp = add(minirt->scene->cam.pos, mult(v, t[0]));
	if (dot(sub(v, extrem[0]), cyl->dir) < 0 || dot(sub(v, extrem[1]), cyl->dir) > 0)
		return ;
	if (closest->init && distance(tmp, minirt->scene->cam.pos) > distance(closest->pos, minirt->scene->cam.pos))
		return ;
	closest->pos = tmp;
	closest->raw_colour = cyl->rgb;
	closest->normal = normal(tmp, cyl);
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
