/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseniak <nseniak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 16:40:47 by nseniak           #+#    #+#             */
/*   Updated: 2023/01/24 16:41:03 by nseniak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	in_cone(t_cone *cone, t_vect pos)
{
	(void)cone;
	(void)pos;
	if (dot(sub(pos, cone->pos), cone->dir) < 0)
		return (0);
	if (dot(sub(pos, cone->top), cone->dir) > 0)
		return (0);
	return (1);
}
