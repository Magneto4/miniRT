/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseniak <nseniak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 18:56:15 by nseniak           #+#    #+#             */
/*   Updated: 2023/01/09 16:08:20 by nseniak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_point	*calculate_intersection(t_minirt *minirt, t_vect v, t_vect src)
{
	t_point		*closest;

	closest = malloc(sizeof(*closest));
	closest->init = 0;
	closest_sphere(minirt, v, closest, src);
	closest_cylinder(minirt, v, closest, src);
	closest_plane(minirt, v, closest, src);
	if (closest->init)
		return (closest);
	free (closest);
	return (NULL);
}
