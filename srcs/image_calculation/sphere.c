/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseniak <nseniak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 22:35:55 by nseniak           #+#    #+#             */
/*   Updated: 2023/01/24 19:49:54 by nseniak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vect	normal_sphere(t_sphere *sphere, t_vect inter, t_vect src)
{
	t_vect	n;

	n = sub(inter, sphere->pos);
	if (distance(src, sphere->pos) < sphere->radius)
		n = mult(n, -1);
	n = mult(n, 1 / sphere->radius);
	return (n);
}

void	sphere_inter(t_vect v, t_vect src, t_sphere *sphere, t_point *closest)
{
	double	t[2];
	t_vect	tmp;
	t_vect	quad;

	tmp = sub(src, sphere->pos);
	quad.x = 1;
	quad.y = dot(v, tmp) * 2;
	quad.z = dot(tmp, tmp) - sphere->radius * sphere->radius;
	if (solve_quadratic(quad, t, t + 1) == 0)
		return ;
	if (t[1] < EPSILON)
		return ;
	if (t[0] < EPSILON)
		t[0] = t[1];
	if (closest->init && t[0] > closest->t)
		return ;
	closest->t = t[0];
	closest->pos = add(src, mult(v, t[0]));
	closest->rgb = sphere->rgb;
	closest->init = SP;
	closest->normal = normal_sphere(sphere, closest->pos, src);
	closest->shape = sphere;
	return ;
}

void	closest_sphere(t_minirt *minirt, t_ray ray, t_point *closest)
{
	t_list	*spheres;

	spheres = minirt->scene->sphere;
	while (spheres)
	{
		sphere_inter(ray.dir, ray.src, (t_sphere *)(spheres->value), closest);
		spheres = spheres->next;
	}
}
