/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseniak <nseniak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 18:56:00 by nseniak           #+#    #+#             */
/*   Updated: 2023/01/12 16:07:54 by nseniak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	calculate_colour(t_minirt *minirt, t_point *point, t_vect v)
{
	t_ambiant	al;
	t_list		*lights;
	t_light		*light;
	t_point		*inter;
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
		ray.src = point->pos;
		inter = calculate_intersection(minirt, ray, point->shape);
		if (dot(point->normal, ray.dir) > 0 || inter->init == 0)
		{
			point->lit_colour.r += light->rgb.r * light->ratio * point->raw_colour.r * dot(point->normal, ray.dir);
			point->lit_colour.g += light->rgb.g * light->ratio * point->raw_colour.g * dot(point->normal, ray.dir);
			point->lit_colour.b += light->rgb.b * light->ratio * point->raw_colour.b * dot(point->normal, ray.dir);
		}
		free(inter);
		lights = lights->next;
	}
	point->lit_colour.r /= 255;
	point->lit_colour.g /= 255;
	point->lit_colour.b /= 255;
	(void)v;
	return (0);
}
