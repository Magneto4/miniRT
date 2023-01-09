/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseniak <nseniak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 22:38:15 by nseniak           #+#    #+#             */
/*   Updated: 2023/01/09 16:16:33 by nseniak          ###   ########.fr       */
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

void	print_vect(t_vect v)
{
	printf("(%f, %f, %f)\n", v.x, v.y, v.z);
}

void	cylinder_inter(t_vect v, t_vect src, t_cylinder *cyl, t_point *closest)
{
	t_vect	r;
	t_vect	va;
	t_vect	quad;
	t_vect	tmp;
	t_vect	extrem[2];
	double	t[2];

	extrem[0] = sub(cyl->pos, mult(cyl->dir, cyl->height / 2));
	extrem[1] = add(cyl->pos, mult(cyl->dir, cyl->height / 2));
	// print_vect(extrem[0]);
	// print_vect(extrem[1]);
	r = cross(cyl->dir, sub(src, extrem[1]));
	r = cross(r, cyl->dir);
	va = cross(cyl->dir, v);
	va = cross(va, cyl->dir);
	quad.x = dot(va, va);
	quad.y = 2 * dot(r, va);
	quad.z = dot(r, r) - cyl->radius * cyl->radius;
	if (solve_quadratic(quad, t, t + 1) == 0)
		return ;
	if (t[1] < 1)
		return ;
	if (t[0] < 1)
		t[0] = t[1];
	tmp = add(src, mult(v, t[0]));
	// if (dot(sub(tmp, extrem[0]), cyl->dir) < 0)
	// 	return ;
	// if (dot(sub(tmp, extrem[1]), cyl->dir) > 0)
	// 	return ;
	if (closest->init && distance(tmp, src) > distance(closest->pos, src))
		return ;
	closest->pos = tmp;
	closest->raw_colour = cyl->rgb;
	closest->normal = normal(tmp, cyl);
	closest->init = 1;
	return ;
}

void	closest_cylinder(t_minirt *minirt, t_vect v, t_point *closest, t_vect src)
{
	t_list	*cylinders;

	cylinders = minirt->scene->cylinder;
	while (cylinders)
	{
		cylinder_inter(v, src, (t_cylinder *)(cylinders->value), closest);
		cylinders = cylinders->next;
	}
}
