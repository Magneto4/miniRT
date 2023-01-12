/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseniak <nseniak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 22:35:55 by nseniak           #+#    #+#             */
/*   Updated: 2023/01/12 23:01:47 by nseniak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
	if (t[1] < 0)
		return ;
	if (t[0] < 0)
		t[0] = t[1];
	tmp = add(src, mult(v, t[0]));
	if (closest->init && distance(tmp, src) > distance(closest->pos, src))
		return ;
	closest->pos = tmp;
	closest->raw_colour = sphere->rgb;
	closest->init = 1;
	closest->normal = sub(closest->pos, sphere->pos);
	closest->shape = sphere;
	normalise(&(closest->normal));
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
