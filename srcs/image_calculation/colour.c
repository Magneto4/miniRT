/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseniak <nseniak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 18:56:00 by nseniak           #+#    #+#             */
/*   Updated: 2023/01/04 16:14:54 by nseniak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	calculate_colour(t_minirt *minirt, t_point *point)
{
	point->lit_colour.r = point->raw_colour.r;
	point->lit_colour.g = point->raw_colour.g;
	point->lit_colour.b = point->raw_colour.b;
	(void)minirt;
	return (0);
}
