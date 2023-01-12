/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseniak <nseniak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 18:56:15 by nseniak           #+#    #+#             */
/*   Updated: 2023/01/12 16:05:56 by nseniak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_point	*calculate_intersection(t_minirt *minirt, t_ray ray, void *exclude)
{
	t_point		*closest;

	closest = malloc(sizeof(*closest));
	closest->init = 0;
	closest_sphere(minirt, ray, closest, exclude);
	closest_cylinder(minirt, ray, closest, exclude);
	closest_plane(minirt, ray, closest, exclude);
	return (closest);
}
