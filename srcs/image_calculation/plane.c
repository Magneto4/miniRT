/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseniak <nseniak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 22:38:23 by nseniak           #+#    #+#             */
/*   Updated: 2023/01/12 15:12:29 by nseniak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
	closest->normal = plane->dir;
	closest->shape = (void *)plane;
	closest->init = 1;
	return ;
}

void	closest_plane(t_minirt *minirt, t_ray ray, t_point *closest, void *exclude)
{
	t_list	*planes;

	planes = minirt->scene->plane;
	while (planes)
	{
		if (exclude != planes->value)
			plane_inter(ray.dir, ray.src, (t_plane *)(planes->value), closest);
		planes = planes->next;
	}
}
