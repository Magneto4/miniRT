/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseniak <nseniak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 18:56:00 by nseniak           #+#    #+#             */
/*   Updated: 2023/01/05 20:29:01 by nseniak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	intensity(double colour, double ratio)
{
	return(colour / 255 * ratio);
}

int	calculate_colour(t_minirt *minirt, t_point *point, t_vect v)
{
	t_ambiant	al;
	t_list		*lights;
	t_light		*light;
	t_vect		orientation;

	al = minirt->scene->al;
	point->lit_colour.r = al.rgb.r / 255 * al.ratio * point->raw_colour.r;
	point->lit_colour.g = al.rgb.g / 255 * al.ratio * point->raw_colour.g;
	point->lit_colour.b = al.rgb.b / 255 * al.ratio * point->raw_colour.b;
	lights = minirt->scene->lights;
	while (lights)
	{
		light = (t_light *)(lights->value);
		orientation = sub(light->pos, point->pos);
		normalise(&orientation);
		if (dot(point->normal, orientation) > 0)
		{
			point->lit_colour.r += light->rgb.r / 255 * light->ratio * point->raw_colour.r * dot(point->normal, orientation);
			point->lit_colour.g += light->rgb.g / 255 * light->ratio * point->raw_colour.g * dot(point->normal, orientation);
			point->lit_colour.b += light->rgb.b / 255 * light->ratio * point->raw_colour.b * dot(point->normal, orientation);
		}
		lights = lights->next;
	}
	(void)v;
	return (0);
}
