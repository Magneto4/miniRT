/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseniak <nseniak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 18:56:00 by nseniak           #+#    #+#             */
/*   Updated: 2023/01/17 19:55:36 by nseniak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	check_inside_sphere(t_minirt *minirt, t_light *light, t_sphere *sphere)
{
	if (distance(minirt->scene->cam.pos, sphere->pos) < sphere->radius)
	{
		if (distance(sphere->pos, light->pos) > sphere->radius)
			return (1); 
	}
	return (0);
}

// int	check_inside_cylinder(t_minirt *minirt, t_light *light, t_cylinder *cylinder)
// {
// 	(void)minirt;
// 	(void)light;
// 	(void)cylinder;
// 	return (0);
// }

int	lit(t_light *light, t_point *point, t_minirt *minirt)
{
	t_point	*inter;
	t_ray	ray;

	ray.dir = sub(point->pos, light->pos);
	normalise(&(ray.dir));
	ray.src = light->pos;
	inter = calculate_intersection(minirt, ray);
	if (inter->init && inter->shape != point->shape)
	{
		free(inter);
		return (0);
	}
	free(inter);
	if (point->init == SP)
	{
		if (check_inside_sphere(minirt, light, (t_sphere *)point->shape))
			return (0);
	}
	// if (point->init == CY)
	// {
	// 	if (check_inside_cylinder(minirt, light, (t_cylinder *)point->shape))
	// 		return (0);
	// }
	return (1);
}

int	calculate_colour(t_minirt *minirt, t_point *point, t_vect v)
{
	t_ambiant	al;
	t_list		*lights;
	t_light		*light;
	t_ray		ray;

	al = minirt->scene->al;
	point->lit_colour.r = al.rgb.r * al.ratio * point->raw_colour.r;
	point->lit_colour.g = al.rgb.g * al.ratio * point->raw_colour.g;
	point->lit_colour.b = al.rgb.b * al.ratio * point->raw_colour.b;
	lights = minirt->scene->lights;
	while (lights)
	{
		light = (t_light *)(lights->value);
		ray.dir = sub(light->pos, point->pos);
		normalise(&(ray.dir));
		ray.src = light->pos;
		if (dot(point->normal, ray.dir) > 0 && lit(light, point, minirt))
		{
			point->lit_colour.r += light->rgb.r * light->ratio * point->raw_colour.r * dot(point->normal, ray.dir);
			point->lit_colour.g += light->rgb.g * light->ratio * point->raw_colour.g * dot(point->normal, ray.dir);
			point->lit_colour.b += light->rgb.b * light->ratio * point->raw_colour.b * dot(point->normal, ray.dir);
		}
		lights = lights->next;
	}
	point->lit_colour.r /= 255;
	point->lit_colour.g /= 255;
	point->lit_colour.b /= 255;
	(void)v;
	return (0);
}
