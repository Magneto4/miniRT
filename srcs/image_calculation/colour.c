/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseniak <nseniak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 18:56:00 by nseniak           #+#    #+#             */
/*   Updated: 2023/01/24 19:36:11 by nseniak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	add_diffuse(t_point *point, t_ray ray, t_light *light)
{
	if (dot(point->normal, ray.dir) < 0)
		return ;
	point->lit_rgb.r += light->rgb.r * light->ratio * \
	point->rgb.r * dot(point->normal, ray.dir);
	point->lit_rgb.g += light->rgb.g * light->ratio * \
	point->rgb.g * dot(point->normal, ray.dir);
	point->lit_rgb.b += light->rgb.b * light->ratio * \
	point->rgb.b * dot(point->normal, ray.dir);
}

void	parse_lights(t_minirt *minirt, t_point *point)
{
	t_list	*lights;
	t_light	*light;
	t_ray	ray;

	lights = minirt->scene->lights;
	while (lights)
	{
		light = (t_light *)(lights->value);
		ray.dir = sub(light->pos, point->pos);
		normalise(&(ray.dir));
		ray.src = light->pos;
		if (lit(light, point, minirt))
			add_diffuse(point, ray, light);
		lights = lights->next;
	}
}

int	calculate_colour(t_minirt *minirt, t_point *point)
{
	t_ambiant	al;

	al = minirt->scene->al;
	point->lit_rgb.r = al.rgb.r * al.ratio * point->rgb.r;
	point->lit_rgb.g = al.rgb.g * al.ratio * point->rgb.g;
	point->lit_rgb.b = al.rgb.b * al.ratio * point->rgb.b;
	parse_lights(minirt, point);
	point->lit_rgb.r /= 255;
	point->lit_rgb.g /= 255;
	point->lit_rgb.b /= 255;
	return (0);
}
