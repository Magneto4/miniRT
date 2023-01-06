/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseniak <nseniak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 22:38:15 by nseniak           #+#    #+#             */
/*   Updated: 2023/01/06 18:39:53 by nseniak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	cylinder_inter(t_vect v, t_minirt *minirt, t_cylinder *cylinder, t_point *closest)
{
	// t_vect	tmp;
	// float	t;

	// closest->pos = tmp;
	// closest->raw_colour = cylinder->rgb;
	// closest->normal = cylinder->dir;
	// closest->init = 1;
	(void)v;
	(void)minirt;
	(void)cylinder;
	(void)closest;
	return ;
}

void	closest_cylinder(t_minirt *minirt, t_vect v, t_point *closest)
{
	t_list	*cylinders;

	cylinders = minirt->scene->cylinder;
	while (cylinders)
	{
		cylinder_inter(v, minirt, (t_cylinder *)(cylinders->value), closest);
		cylinders = cylinders->next;
	}
}
