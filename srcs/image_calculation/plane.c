/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngiroux <ngiroux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 22:38:23 by nseniak           #+#    #+#             */
/*   Updated: 2023/01/14 19:50:40 by ngiroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vect	plane_normal(t_plane *plane, t_vect src, t_vect inter)
{
	t_vect	n;

	if (dot(sub(src, inter), plane->dir) < 0)
		n = mult(plane->dir, -1);
	else
		n = plane->dir;
	return (n);
}

void	plane_inter(t_ray ray, t_plane *plane, t_point *closest)
{
	float	a;
	float	b;
	float	t;

	a = dot(plane->dir, sub(ray.src, plane->pos));
	b = dot(plane->dir, ray.dir);
	if (b == 0)
		return ;
	t = -a / b;
	if (t < EPSILON)
		return ;
	if (closest->init && t > closest->t)
		return ;
	closest->t = t;
	closest->pos = add(ray.src, mult(ray.dir, t));
	closest->raw_colour = plane->rgb;
	closest->normal = plane_normal(plane, ray.src, closest->pos);
	closest->shape = plane;
	closest->init = PL;
	return ;
}

void	closest_plane(t_minirt *minirt, t_ray ray, t_point *closest)
{
	t_list	*planes;

	planes = minirt->scene->plane;
	while (planes)
	{
		plane_inter(ray, (t_plane *)(planes->value), closest);
		planes = planes->next;
	}
}
