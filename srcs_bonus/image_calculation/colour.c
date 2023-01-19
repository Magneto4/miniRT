/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseniak <nseniak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 18:56:00 by nseniak           #+#    #+#             */
/*   Updated: 2023/01/19 16:42:30 by nseniak          ###   ########.fr       */
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

int	lit(t_light *light, t_point *point, t_minirt *minirt)
{
	t_ray	ray;

	ray.dir = sub(point->pos, light->pos);
	normalise(&(ray.dir));
	ray.src = light->pos;
	if (shaded(minirt, ray, point->shape))
		return (0);
	if (point->init == SP)
	{
		if (check_inside_sphere(minirt, light, (t_sphere *)point->shape))
			return (0);
	}
	return (1);
}

void	add_diffuse(t_point *point, t_ray ray, t_light *light)
{
	double	x;

	x = dot(point->normal, ray.dir);
	if (x < 0)
		return ;
	point->lit_rgb.r += light->rgb.r * light->ratio * \
	point->rgb.r * x;
	point->lit_rgb.g += light->rgb.g * light->ratio * \
	point->rgb.g * x;
	point->lit_rgb.b += light->rgb.b * light->ratio * \
	point->rgb.b * x;
}

void	add_specular(t_point *point, t_ray ray, t_light *light, t_vect v)
{
	t_vect	r;
	double	x;

	r = mult(point->normal, -2 * dot(ray.dir, point->normal));
	r = add (ray.dir, r);
	normalise(&r);
	x = dot(r, v);
	if (x < 0)
		return ;
	point->n = 100;
	point->lit_rgb.r += light->rgb.r * light->ratio * point->rgb.r * pow(x, point->n);
	point->lit_rgb.g += light->rgb.g * light->ratio * point->rgb.g * pow(x, point->n);
	point->lit_rgb.b += light->rgb.b * light->ratio * point->rgb.b * pow(x, point->n);
}

void	parse_lights(t_minirt *minirt, t_point *point, t_vect v)
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
		{
			add_diffuse(point, ray, light);
			add_specular(point, ray, light, v);
		}
		lights = lights->next;
	}
	(void)v;
}

int	calculate_colour(t_minirt *minirt, t_point *point, t_vect v)
{
	t_ambiant	al;

	texturing(point);
	// if (point->init == SP)
	// 	printf("%i %i %i\n", point->rgb.r, point->rgb.g, point->rgb.b);
	al = minirt->scene->al;
	point->lit_rgb.r = al.rgb.r * al.ratio * point->rgb.r;
	point->lit_rgb.g = al.rgb.g * al.ratio * point->rgb.g;
	point->lit_rgb.b = al.rgb.b * al.ratio * point->rgb.b;
	parse_lights(minirt, point, v);
	point->lit_rgb.r /= 255;
	point->lit_rgb.g /= 255;
	point->lit_rgb.b /= 255;
	(void)v;
	return (0);
}
