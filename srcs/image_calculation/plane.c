/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseniak <nseniak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 22:38:23 by nseniak           #+#    #+#             */
/*   Updated: 2023/01/06 18:20:01 by nseniak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	plane_inter(t_vect v, t_minirt *minirt, t_plane *plane, t_point *closest)
{
	t_vect	tmp;
	float	a;
	float	b;
	float	t;

	a = dot(plane->dir, sub(minirt->scene->cam.pos, plane->pos));
	b = dot(plane->dir, v);
	if (b == 0)
		return ;
	t = - a / b;
	if (t < 0)
		return ;
	tmp.x = t * v.x + minirt->scene->cam.pos.x;	
	tmp.y = t * v.y + minirt->scene->cam.pos.y;
	tmp.z = t * v.z + minirt->scene->cam.pos.z;
	if (closest->init && distance(tmp, minirt->scene->cam.pos) > distance(closest->pos, minirt->scene->cam.pos))
		return ;
	closest->pos = tmp;
	closest->raw_colour = plane->rgb;
	closest->normal = plane->dir;
	closest->init = 1;
	return ;
}

void	closest_plane(t_minirt *minirt, t_vect v, t_point *closest)
{
	t_list	*planes;

	planes = minirt->scene->plane;
	while (planes)
	{
		plane_inter(v, minirt, (t_plane *)(planes->value), closest);
		planes = planes->next;
	}
}
