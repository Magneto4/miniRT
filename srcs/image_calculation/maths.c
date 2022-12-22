/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseniak <nseniak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 22:18:40 by nseniak           #+#    #+#             */
/*   Updated: 2022/12/22 22:41:45 by nseniak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	norm(t_vect *v)
{
	return (sqrt(v->x * v->x + v->y * v->y + v->z * v->z));
}

void	normalise(t_vect *v)
{
	double	n;

	n = norm(v);
	v->x = v->x / n;
	v->y = v->y / n;
	v->z = v->z / n;
}

double	distance(t_vect *a, t_vect *b)
{
	double	dis;

	dis = (a->x - b->x) * (a->x - b->x);
	dis += (a->y - b->y) * (a->y - b->y);
	dis += (a->z - b->z) * (a->z - b->z);
	return(sqrt(dis));
}
