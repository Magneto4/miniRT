/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseniak <nseniak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 11:58:33 by nseniak           #+#    #+#             */
/*   Updated: 2023/01/19 15:43:00 by nseniak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vect	normal_cone(t_vect p, t_cone *cone)
{
	t_vect	normal;
	t_vect	axproj;
	t_vect	axperp;
	t_vect	ip;

	ip = sub(cone->top, p);
	axproj = add(cone->pos, mult(cone->dir, dot(ip, cone->dir) / dot(cone->dir, cone->dir)));
	axperp = sub(p, axproj);
	normal = cross(ip, cross(axperp, ip));
	normalise(&normal);
	return (normal);
}

int	in_cone(t_cone *cone, t_vect pos)
{
	(void)cone;
	(void)pos;
	if (dot(sub(pos, cone->pos), cone->dir) < 0)
		return (0);
	if (dot(sub(pos, cone->top), cone->dir) > 0)
		return (0);
	return (1);
}

int	best_t_cone(double *t, t_ray ray, t_cone *cone)
{
	if (t[1] < EPSILON)
		return (1);
	if (t[0] < EPSILON)
	{
		t[0] = t[1];
		if (!in_cone(cone, add(ray.src, mult(ray.dir, t[0]))))
			return (1);
	}
	else
	{
		if (!in_cone(cone, add(ray.src, mult(ray.dir, t[0]))))
		{
			if (!in_cone(cone, add(ray.src, mult(ray.dir, t[1]))))
				return (1);
			else
				t[0] = t[1];
		}
	}
	return (0);
}



void	cone_inter(t_ray ray, t_cone *cone, t_point *closest)
{
	t_vect	quad;
	double	m;
	t_vect	w;
	double	t[2];

	m = cone->radius * cone->radius / cone->height / cone->height;
	w = sub(ray.src, cone->top);
	t[0] = dot(ray.dir, cone->dir);
	t[1] = dot(w, cone->dir);
	quad.x = dot(ray.dir, ray.dir) - (m + 1) * t[0] * t[0];
	quad.y = 2 * (dot(ray.dir, w) - (m + 1) * t[0] * t[1]);
	quad.z = dot(w, w) - (m + 1) * t[1] * t[1];
	if (solve_quadratic(quad, t, t + 1) == 0)
		return ;
	if (best_t_cone(t, ray, cone))
		return ;
	if (closest->init && t[0] >= closest->t)
		return ;
	closest->t = t[0];
	closest->pos = add(ray.src, mult(ray.dir, t[0]));
	closest->rgb = cone->rgb;
	closest->init = CO;
	closest->normal = normal_cone(closest->pos, cone);
	closest->shape = cone;
	closest->checkered = cone->checkered;
	return ;
}

void	cap_inter(t_ray ray, t_cone *cone, t_point *closest)
{
	t_point	point;
	t_plane	plane;

	point.init = 0;
	plane.dir = cone->dir;
	plane.pos = cone->pos;
	plane.rgb = cone->rgb;
	plane_inter(ray, &plane, &point);
	if (!(point.init) || distance(plane.pos, point.pos) > cone->radius)
		return ;
	if (point.t > closest->t)
		return ;
	closest->t = point.t;
	closest->pos = point.pos;
	closest->rgb = cone->rgb;
	closest->init = CO;
	closest->normal = point.normal;
	closest->shape = cone;
	closest->checkered = cone->checkered;
}


void	closest_cone(t_minirt *minirt, t_ray ray, t_point *closest)
{
	t_list	*cones;

	cones = minirt->scene->cone;
	while (cones)
	{
		cone_inter(ray, (t_cone *)(cones->value), closest);
		cap_inter(ray, (t_cone *)(cones->value), closest);
		cones = cones->next;
	}
}
