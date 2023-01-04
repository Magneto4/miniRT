/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseniak <nseniak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 22:35:55 by nseniak           #+#    #+#             */
/*   Updated: 2023/01/04 16:15:48 by nseniak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// void	fill_value(t_point *point, float t, t_vect v, t_vect *pos, t_rgb *rgb)
// {
// 	point->pos->x = pos->x + t * v.x;
// 	point->pos->y = pos->y + t * v.y;
// 	point->pos->z = pos->z + t * v.z;
// 	point->raw_colour->r = rgb->r;
// 	point->raw_colour->g = rgb->g;
// 	point->raw_colour->b = rgb->b;
// }

void	sphere_inter(t_vect v, t_minirt *minirt, t_sphere *sphere, t_point *closest)
{
	float	b;
	float	c;
	float	discriminant;
	float	t1;
	float	t2;
	t_vect	tmp;

	tmp = sub(*(minirt->scene->cam->pos), *(sphere->pos));
	b = dot(v, tmp);
	b *= 2.;
	c = dot(tmp, tmp) - sphere->radius * sphere->radius;
	discriminant = b * b - 4. * c;
	if (discriminant < 0)
		return ;
	t1 = (-b - sqrt(discriminant)) / 2.;
	t2 = (-b + sqrt(discriminant)) / 2.;
	if (t2 < 0)
		return ;
	if (t1 < 0)
		t1 = t2;
	tmp.x = minirt->scene->cam->pos->x + t1 * v.x;
	tmp.y = minirt->scene->cam->pos->y + t1 * v.y;
	tmp.z = minirt->scene->cam->pos->z + t1 * v.z;
	if (closest->init == 0)
	{
		closest->pos = tmp;
		closest->raw_colour.r = sphere->rgb->r;
		closest->raw_colour.g = sphere->rgb->g;
		closest->raw_colour.b = sphere->rgb->b;
		closest->init = 1;
		return ;
	}
	if (distance(tmp, *(minirt->scene->cam->pos)) > distance(closest->pos, *(minirt->scene->cam->pos)))
		return ;
	closest->pos = tmp;
	closest->raw_colour.r = sphere->rgb->r;
	closest->raw_colour.g = sphere->rgb->g;
	closest->raw_colour.b = sphere->rgb->b;
	closest->init = 1;
	return ;
}

void	closest_sphere(t_minirt *minirt, t_vect v, t_point *closest)
{
	t_list	*spheres;

	spheres = minirt->scene->sphere;
	while (spheres)
	{
		sphere_inter(v, minirt, (t_sphere *)(spheres->value), closest);
		spheres = spheres->next;
	}
}
