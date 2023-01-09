/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_types.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngiroux <ngiroux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 13:11:40 by ngiroux           #+#    #+#             */
/*   Updated: 2023/01/09 15:46:45 by ngiroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	set_couple(char **data, t_couple *couple)
{
	char	**split;

	split = split_set(data[0], ",");
	if (split == NULL)
		return ;
	couple->x = __atoi(split[0]);
	couple->y = __atoi(split[1]);
	free_tab(split);
}

void	set_vector(char **data, t_vect *vector)
{
	char	**split;

	split = split_set(data[0], ",");
	if (split == NULL)
		return ;
	vector->x = __atod(split[0]);
	vector->y = __atod(split[1]);
	vector->z = __atod(split[2]);
	free_tab(split);
}

void	set_rgb(char **data, t_rgb *rgb)
{
	char	**split;

	split = split_set(data[0], ",");
	if (split == NULL)
		return ;
	rgb->r = __atoi(split[0]);
	rgb->g = __atoi(split[1]);
	rgb->b = __atoi(split[2]);
	free_tab(split);
}