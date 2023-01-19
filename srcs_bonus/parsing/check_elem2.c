/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_elem2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseniak <nseniak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 19:43:03 by ngiroux           #+#    #+#             */
/*   Updated: 2023/01/19 14:15:29 by nseniak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	check_sphere(char **data)
{
	if (__wordcount(data) != 3)
		return (false);
	if (check_vector(data[0]) == false)
		return (false);
	if (check_double(data[1]) == false)
		return (false);
	if (__atod(data[1]) < 0)
		return (false);
	if (check_rgb(data[2]) == false)
		return (false);
	return (true);
}

bool	check_plane(char **data)
{
	if (__wordcount(data) != 3)
		return (false);
	if (check_vector(data[0]) == false)
		return (false);
	if (check_vector_norm(data[1]) == false)
		return (false);
	if (check_rgb(data[2]) == false)
		return (false);
	return (true);
}

bool	check_cylinder(char **data)
{
	if (__wordcount(data) != 5)
		return (false);
	if (check_vector(data[0]) == false)
		return (false);
	if (check_vector_norm(data[1]) == false)
		return (false);
	if (check_double(data[2]) == false)
		return (false);
	if (__atod(data[2]) < 0)
		return (false);
	if (check_double(data[3]) == false)
		return (false);
	if (__atod(data[3]) < 0)
		return (false);
	if (check_rgb(data[4]) == false)
		return (false);
	return (true);
}
