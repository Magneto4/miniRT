/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_elem.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngiroux <ngiroux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 12:57:05 by ngiroux           #+#    #+#             */
/*   Updated: 2023/01/14 18:22:37 by ngiroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	check_ambiant(char **data)
{
	if (__wordcount(data) != 2)
		return (false);
	if (check_double(data[0]) == false)
		return (false);
	if (__atod(data[0]) < 0 || __atod(data[0]) > 1)
		return (false);
	if (check_rgb(data[1]) == false)
		return (false);
	return (true);
}

bool	check_camera(char **data)
{
	if (__wordcount(data) != 3)
		return (false);
	if (check_vector(data[0]) == false)
		return (false);
	if (check_vector_norm(data[1]) == false)
		return (false);
	if (check_double(data[2]) == false)
		return (false);
	if (__atod(data[2]) < 0 || __atod(data[2]) > 180)
		return (false);
	return (true);
}

bool	check_light(char **data)
{
	if (__wordcount(data) != 3 && BONUS == 0)
		return (false);
	if (__wordcount(data) > 4 && __wordcount(data) < 3 && BONUS == 1)
		return (false);
	if (check_vector(data[0]) == false)
		return (false);
	if (check_double(data[1]) == false)
		return (false);
	if (__atod(data[1]) < 0 || __atod(data[1]) > 1)
		return (false);
	if (data[2] != NULL && BONUS == 1)
		if (check_rgb(data[2]) == false)
			return (false);
	return (true);
}

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
