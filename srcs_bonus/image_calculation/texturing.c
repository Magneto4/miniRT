/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texturing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseniak <nseniak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 15:39:19 by nseniak           #+#    #+#             */
/*   Updated: 2023/02/03 16:12:50 by nseniak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	checkering(t_point *point, t_vect2 coord)
{
	int	n;
	int	m;

	n = 1;
	while (n <= CHECKER)
	{
		m = 1;
		while (m <= CHECKER)
		{
			if (coord.u <= n / CHECKER && coord.v <= m / CHECKER)
			{
				if ((n + m) % 2)
					point->rgb = int_to_rgb(0x000000);
				else
					point->rgb = int_to_rgb(0xffffff);
				return ;
			}
			m ++;
		}
		n ++;
	}
}

void	texturing(t_point *point)
{
	t_vect2	coord;

	if (!(point->bonus.checkered))
		return ;
	coord = flat_coord(point);
	checkering(point, coord);
	if (point->bonus.textured)
		normal_mapping(point, coord);
}
