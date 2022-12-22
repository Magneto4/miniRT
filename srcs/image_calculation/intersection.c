/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseniak <nseniak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 18:56:15 by nseniak           #+#    #+#             */
/*   Updated: 2022/12/22 22:44:25 by nseniak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	free_point(t_point *point)
{
	if (!point)
		return ;
	free(point->lit_colour);
	free(point->normal);
	free(point->lit_colour);
	free(point->pos);
	free(point);
}

t_vect *orientation_vector(t_minirt *minirt, double x, double y)
{
	t_vect		*v;
	t_camera	*cam;

	cam = minirt->scene->cam;
	v = malloc(sizeof(*v));
	if (!v)
		clean_end(minirt);
	//calculate the direction vector, it's just maths
	v->x = sin (cam->dir->x * PI + cam->fov * ((x / F_WIDTH - 0.5) / 180. * PI));
	v->y = cos (cam->dir->x * PI + cam->fov * (x / F_HEIGHT - 0.5) / 180. * PI);
	v->z = cam->fov * PI / 180. * F_HEIGHT / F_WIDTH * (y /HEIGHT - 0.5);
	normalise(v);
	return (v);
}

t_point	*calculate_intersection(t_minirt *minirt, int x, int y)
{
	t_point		*closest;
	t_point		*point;
	t_vect		*v;
	t_camera	*cam;

	cam = minirt->scene->cam;
	v = orientation_vector(minirt, (double)x, (double)y);
	closest = closest_sphere(minirt, v);
	point = closest_cylinder(minirt, v);
	if (!closest || (point && distance(closest->pos, cam->pos) > distance(point->pos, cam->pos)))
	{
		free_point(closest);
		closest = point;
	}
	else
		free_point(point);
	point = closest_plane(minirt, v);
	if (!closest || (point && distance(closest->pos, cam->pos) > distance(point->pos, cam->pos)))
	{
		free_point(closest);
		closest = point;
	}
	else
		free_point(point);
	free(v);
	free_point(closest);
	return (NULL);
}
