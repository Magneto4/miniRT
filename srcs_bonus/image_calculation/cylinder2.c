/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseniak <nseniak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 18:38:03 by nseniak           #+#    #+#             */
/*   Updated: 2023/01/24 18:41:25 by nseniak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vect	normal_cylinder(t_vect p, t_cylinder *cyl, t_vect src)
{
	t_vect	tmp;
	t_vect	normal;

	tmp = sub(p, cyl->pos);
	normal = sub(tmp, mult(cyl->dir, dot(cyl->dir, tmp)));
	if (norm(cross(sub(src, cyl->pos), cyl->dir)) <= cyl->radius)
		normal = mult(normal, -1);
	normalise(&normal);
	return (normal);
}

int	in_cyl(t_cylinder *cyl, t_vect pos)
{
	if (dot(sub(pos, cyl->pos), cyl->dir) < 0)
		return (0);
	if (dot(sub(pos, cyl->top), cyl->dir) > 0)
		return (0);
	return (1);
}

int	best_t(double *t, t_ray ray, t_cylinder *cyl)
{
	if (t[1] < EPSILON)
		return (1);
	if (t[0] < EPSILON)
	{
		t[0] = t[1];
		if (!in_cyl(cyl, add(ray.src, mult(ray.dir, t[0]))))
			return (1);
	}
	else
	{
		if (!in_cyl(cyl, add(ray.src, mult(ray.dir, t[0]))))
		{
			if (!in_cyl(cyl, add(ray.src, mult(ray.dir, t[1]))))
				return (1);
			else
				t[0] = t[1];
		}
	}
	return (0);
}
