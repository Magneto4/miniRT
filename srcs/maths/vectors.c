/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseniak <nseniak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 23:38:21 by nseniak           #+#    #+#             */
/*   Updated: 2023/01/17 23:40:32 by nseniak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	norm(t_vect v)
{
	return (sqrt(dot(v, v)));
}

void	normalise(t_vect *v)
{
	double	n;

	n = norm(*v);
	v->x = v->x / n;
	v->y = v->y / n;
	v->z = v->z / n;
}

double	distance(t_vect a, t_vect b)
{
	double	dis;

	dis = (a.x - b.x) * (a.x - b.x);
	dis += (a.y - b.y) * (a.y - b.y);
	dis += (a.z - b.z) * (a.z - b.z);
	return (sqrt(dis));
}

double	dot(t_vect a, t_vect b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vect	sub(t_vect a, t_vect b)
{
	t_vect	c;

	c.x = a.x - b.x;
	c.y = a.y - b.y;
	c.z = a.z - b.z;
	return (c);
}
