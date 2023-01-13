/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_types.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngiroux <ngiroux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 13:11:40 by ngiroux           #+#    #+#             */
/*   Updated: 2023/01/13 19:36:00 by ngiroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	set_couple(char **data, t_couple *couple)
{
	char	**split;

	if (wordcount_set(data[0], ",") != 2)
		return (false);
	split = split_set(data[0], ",");
	if (split == NULL)
		return (false);
	couple->x = __atoi(split[0]);
	couple->y = __atoi(split[1]);
	free_tab(split);
	return (true);
}

bool	set_vector(char **data, t_vect *vector)
{
	char	**split;
	int		i;

	if (wordcount_set(data[0], ",") != 3)
		return (false);
	split = split_set(data[0], ",");
	if (split == NULL)
		return (false);
	i = -1;
	while (split[++i])
	{
		if (check_double(split[i]) == false)
			return (free_tab(split), false);
	}
	vector->x = __atod(split[0]);
	vector->y = __atod(split[1]);
	vector->z = __atod(split[2]);
	free_tab(split);
	return (true);
}

bool	set_rgb(char **data, t_rgb *rgb)
{
	char	**split;
	double	tmp;
	int		i;

	if (wordcount_set(data[0], ",") != 3)
		return (false);
	split = split_set(data[0], ",");
	if (split == NULL)
		return (false);
	i = -1;
	while (split[++i])
	{
		if (check_int(split[i]) == false)
			return (free_tab(split), false);
		tmp = __atod(split[i]);
		if (tmp > MAX_INT || tmp < MIN_INT)
			return (free_tab(split), false);
		if (tmp > 255 || tmp < 0)
			return (free_tab(split), false);
	}
	rgb->r = __atoi(split[0]);
	rgb->g = __atoi(split[1]);
	rgb->b = __atoi(split[2]);
	free_tab(split);
	return (true);
}
