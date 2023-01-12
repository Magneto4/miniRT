/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseniak <nseniak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 22:38:23 by nseniak           #+#    #+#             */
/*   Updated: 2023/01/12 23:52:40 by nseniak          ###   ########.fr       */
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

void	plane_inter(t_vect v, t_vect src, t_plane *plane, t_point *closest)
{
	t_vect	tmp;
	float	a;
	float	b;
	float	t;

	a = dot(plane->dir, sub(src, plane->pos));
	b = dot(plane->dir, v);
	if (b == 0)
		return ;
	t = - a / b;
	if (t < 0)
		return ;
	tmp = add(src, mult(v, t));
	if (closest->init && distance(tmp, src) > distance(closest->pos, src))
		return ;
	closest->pos = tmp;
	closest->raw_colour = plane->rgb;
	closest->normal = plane_normal(plane, src, tmp);
	closest->shape = plane;
	closest->init = 1;
	return ;
}

void	closest_plane(t_minirt *minirt, t_ray ray, t_point *closest)
{
	t_list	*planes;

	planes = minirt->scene->plane;
	while (planes)
	{
		plane_inter(ray.dir, ray.src, (t_plane *)(planes->value), closest);
		planes = planes->next;
	}
}
