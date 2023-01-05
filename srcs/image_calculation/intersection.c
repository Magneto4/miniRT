/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseniak <nseniak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 18:56:15 by nseniak           #+#    #+#             */
/*   Updated: 2023/01/05 17:20:04 by nseniak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vect orientation_vector(t_minirt *minirt, double x, double y)
{
	t_vect	v;

	v.x = (2 * ((x + 0.5) / F_WIDTH) - 1) * tan(minirt->scene->cam.fov / 2 * M_PI / 180) * F_WIDTH / F_HEIGHT;
	v.y = 1 - 2 * ((y + 0.5) / F_HEIGHT) * tan(minirt->scene->cam.fov / 2 * M_PI / 180);
	v.z = -1;
	normalise(&v);
	return (v);
}

t_point	*calculate_intersection(t_minirt *minirt, int x, int y)
{
	t_point		*closest;
	t_vect		v;
	// t_camera	*cam;

	// cam = minirt->scene->cam;
	v = orientation_vector(minirt, (double)x, (double)y);
	closest = malloc(sizeof(*closest));
	closest->init = 0;
	closest_sphere(minirt, v, closest);
	// point = closest_cylinder(minirt, v, point);
	// if (!closest || (point && distance(*(closest->pos), *(cam->pos)) > distance(*(point->pos), *(cam->pos))))
	// {
	// 	free_point(closest);
	// 	closest = point;
	// }
	// else
	// 	free_point(point);
	// point = closest_plane(minirt, v, point);
	// if (!closest || (point && distance(*(closest->pos), *(cam->pos)) > distance(*(point->pos), *(cam->pos))))
	// {
	// 	free_point(closest);
	// 	closest = point;
	// }
	// else
	// 	free_point(point);
	if (closest->init == 0)
	{
		free (closest);
		return (NULL);
	}
	return (closest);
}
