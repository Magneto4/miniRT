/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_types.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngiroux <ngiroux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 13:11:40 by ngiroux           #+#    #+#             */
/*   Updated: 2023/01/09 13:25:10 by ngiroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

	// if (couple[0] == NULL || couple[1] == NULL)
	// 	return ;
	// add check and protection to stop parsing, maybe change return type

void	set_couple(char **data, t_couple *couple)
{
	couple->x = __atoi(data[0]);
	couple->y = __atoi(data[1]);
}

void	set_vector(char **data, t_vect *vector)
{
	vector->x = __atod(data[0]);
	vector->y = __atod(data[1]);
	vector->z = __atod(data[2]);
}

void	set_rgb(char **data, t_rgb *rgb)
{
	rgb->r = __atoi(data[0]);
	rgb->g = __atoi(data[1]);
	rgb->b = __atoi(data[2]);
}
