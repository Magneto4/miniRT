/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseniak <nseniak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 16:18:07 by nseniak           #+#    #+#             */
/*   Updated: 2023/01/24 19:36:53 by nseniak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	invert(t_mat m, t_mat *inv)
{
	double	det;

	det = m[0][0] * (m[1][1] * m[2][2] - m[2][1] * m[1][2]) \
	- m[0][1] * (m[1][0] * m[2][2] - m[1][2] * m[2][0]) \
	+ m[0][2] * (m[1][0] * m[2][1] - m[1][1] * m[2][0]);
	(*inv)[0][0] = (m[1][1] * m[2][2] - m[2][1] * m[1][2]) / det;
	(*inv)[0][1] = (m[0][2] * m[2][1] - m[0][1] * m[2][2]) / det;
	(*inv)[0][2] = (m[0][1] * m[1][2] - m[0][2] * m[1][1]) / det;
	(*inv)[1][0] = (m[1][2] * m[2][0] - m[1][0] * m[2][2]) / det;
	(*inv)[1][1] = (m[0][0] * m[2][2] - m[0][2] * m[2][0]) / det;
	(*inv)[1][2] = (m[1][0] * m[0][2] - m[0][0] * m[1][2]) / det;
	(*inv)[2][0] = (m[1][0] * m[2][1] - m[2][0] * m[1][1]) / det;
	(*inv)[2][1] = (m[2][0] * m[0][1] - m[0][0] * m[2][1]) / det;
	(*inv)[2][2] = (m[0][0] * m[1][1] - m[1][0] * m[0][1]) / det;
}

t_vect	mat_mult(double mat[3][3], t_vect v)
{
	t_vect	res;

	res.x = v.x * mat[0][0] + v.y * mat[0][1] + v.z * mat[0][2];
	res.y = v.x * mat[1][0] + v.y * mat[1][1] + v.z * mat[1][2];
	res.z = v.x * mat[2][0] + v.y * mat[2][1] + v.z * mat[2][2];
	return (res);
}

int	rgb_to_int(t_rgb rgb)
{
	int	colour;

	if (rgb.r > 255)
		rgb.r = 255;
	if (rgb.g > 255)
		rgb.g = 255;
	if (rgb.b > 255)
		rgb.b = 255;
	colour = rgb.r * 256 * 256;
	colour += rgb.g * 256;
	colour += rgb.b;
	return (colour);
}
