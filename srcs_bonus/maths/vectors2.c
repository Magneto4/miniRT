/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseniak <nseniak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 23:40:23 by nseniak           #+#    #+#             */
/*   Updated: 2023/01/17 23:40:45 by nseniak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vect	mult(t_vect v, double a)
{
	t_vect	w;

	w.x = v.x * a;
	w.y = v.y * a;
	w.z = v.z * a;
	return (w);
}

t_vect	add(t_vect a, t_vect b)
{
	t_vect	c;

	c.x = a.x + b.x;
	c.y = a.y + b.y;
	c.z = a.z + b.z;
	return (c);
}

t_vect	mat_mult(double mat[3][3], t_vect v)
{
	t_vect	res;

	res.x = v.x * mat[0][0] + v.y * mat[0][1] + v.z * mat[0][2];
	res.y = v.x * mat[1][0] + v.y * mat[1][1] + v.z * mat[1][2];
	res.z = v.x * mat[2][0] + v.y * mat[2][1] + v.z * mat[2][2];
	return (res);
}

t_vect	cross(t_vect v, t_vect w)
{
	t_vect	u;

	u.x = v.y * w.z - v.z * w.y;
	u.y = v.z * w.x - v.x * w.z;
	u.z = v.x * w.y - v.y * w.x;
	return (u);
}
