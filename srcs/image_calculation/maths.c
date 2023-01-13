/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseniak <nseniak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 22:18:40 by nseniak           #+#    #+#             */
/*   Updated: 2023/01/13 17:33:28 by nseniak          ###   ########.fr       */
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
	return(sqrt(dis));
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

t_vect	mult(t_vect v, double a)
{
	t_vect w;

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

int	solve_quadratic(t_vect v, double *x1, double *x2)
{
	double	d;
	double	y1;
	double	y2;

	d = v.y * v.y - 4 * v.x * v.z;
	if (d < 0)
		return (0);
	if (d == 0)
	{
		*x1 = - v.y / 2 * v.x;
		*x2 = *x1;
		return (1);
	}
	y1 = (- v.y - sqrt(d)) / 2 * v.x;
	y2 = (- v.y + sqrt(d)) / 2 * v.x;
	if (y1 < y2)
	{
		*x1 = y1;
		*x2 = y2;
	}
	else
	{
		*x1 = y2;
		*x2 = y1;
	}
	return (2);
}

t_vect	cross(t_vect v, t_vect w)
{
	t_vect	u;

	u.x = v.y * w.z - v.z * w.y;
	u.y = v.z * w.x - v.x * w.z;
	u.z = v.x * w.y - v.y * w.x;
	return (u);
}
