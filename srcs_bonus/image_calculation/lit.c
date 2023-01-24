/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseniak <nseniak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 18:57:52 by nseniak           #+#    #+#             */
/*   Updated: 2023/01/24 19:41:07 by nseniak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	check_inside_cyl(t_vect cam_pos, t_light *light, t_cylinder *cyl)
{
	double	d_2;

	d_2 = self_dot(cross(cyl->dir, sub(cyl->pos, cam_pos)));
	if (d_2 > cyl->radius * cyl->radius || !in_cyl(cyl, cam_pos))
		return (0);
	d_2 = self_dot(cross(cyl->dir, sub(cyl->pos, light->pos)));
	if (d_2 > cyl->radius * cyl->radius || !in_cyl(cyl, light->pos))
		return (1);
	return (0);
}

int	check_inside_cone(t_vect cam_pos, t_light *light, t_cone *cone)
{
	double	d_2;
	double	r;
	double	height;

	height = dot(sub(cam_pos, cone->top), cone->dir);
	r = (height / cone->height) * cone->radius;
	d_2 = self_dot(cross(cone->dir, sub(cone->pos, cam_pos)));
	if (d_2 > r * r || !in_cone(cone, cam_pos))
		return (0);
	height = dot(sub(light->pos, cone->top), cone->dir);
	r = (height / cone->height) * cone->radius;
	d_2 = self_dot(cross(cone->dir, sub(cone->pos, light->pos)));
	if (d_2 > r * r || !in_cone(cone, light->pos))
		return (1);
	return (0);
}

int	check_inside_sphere(t_vect cam_pos, t_light *light, t_sphere *sphere)
{
	if (distance(cam_pos, sphere->pos) > sphere->radius)
		return (0);
	if (distance(sphere->pos, light->pos) > sphere->radius)
		return (1);
	return (0);
}

int	lit(t_light *light, t_point *point, t_minirt *minirt)
{
	t_ray	ray;

	ray.dir = sub(point->pos, light->pos);
	normalise(&(ray.dir));
	ray.src = light->pos;
	if (shaded(minirt, ray, point->shape))
		return (0);
	if (point->init == SP && check_inside_sphere(minirt->scene->cam.pos, \
	light, (t_sphere *)point->shape))
		return (0);
	if (point->init == CY || point->init == CY_B || point->init == CY_T)
	{
		if (check_inside_cyl(minirt->scene->cam.pos, \
		light, (t_cylinder *)point->shape))
			return (0);
	}
	if (point->init == CO && check_inside_cone(minirt->scene->cam.pos, \
	light, (t_cone *)point->shape))
		return (0);
	return (1);
}
