/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quadratics.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseniak <nseniak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 23:39:11 by nseniak           #+#    #+#             */
/*   Updated: 2023/01/17 23:39:18 by nseniak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	solve_quadratic(t_vect v, double *x1, double *x2)
{
	double	d;
	double	y1;
	double	y2;

	d = v.y * v.y - 4. * v.x * v.z;
	if (d < 0)
		return (0);
	y1 = (-v.y - sqrt(d)) / 2. / v.x;
	y2 = (-v.y + sqrt(d)) / 2. / v.x;
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
