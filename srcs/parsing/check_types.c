/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_types.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngiroux <ngiroux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 18:23:25 by ngiroux           #+#    #+#             */
/*   Updated: 2023/01/13 19:16:49 by ngiroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
	input => char ** split from whitespaces
	1) check number args
	2) check each arg

	2.1) check number of sub arg (split coma)
	2.2) check numeric value
	2.3) check if in range

	2.4) special check => if null vector or <= 0 for radius
*/

bool	check_double(char *str)
{
	bool	dot;

	dot = false;
	if (*str == '-' || *str == '+')
		str++;
	while (*str)
	{
		if (*str < '0' || *str > '9')
		{
			if (*str == '.' && dot == false)
				dot = true;
			else
				return (false);
		}
		str++;
	}
	return (true);
}

bool	check_int(char *str)
{
	if (*str == '-' || *str == '+')
		str++;
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (false);
		str++;
	}
	return (true);
}

bool	check_vector(char *str)
{
	char	**data;
	bool	ret;

	ret = true;
	data = split_set(str, ",");
	if (__wordcount(data) != 3)
		ret = false;
	if (check_double(data[0]) == false)
		ret = false;
	if (check_double(data[1]) == false)
		ret = false;
	if (check_double(data[2]) == false)
		ret = false;
	free_tab(data);
	return (ret);
}

bool	check_rgb(char *str)
{
	char	**data;
	bool	ret;

	ret = true;
	data = split_set(str, ",");
	if (__wordcount(data) != 3)
		ret = false;
	if (check_int(data[0]) == false)
		ret = false;
	if (check_int(data[1]) == false)
		ret = false;
	if (check_int(data[2]) == false)
		ret = false;
	if (__atoi(data[0]) < 0 || __atoi(data[0]) > 255)
		ret = false;
	if (__atoi(data[1]) < 0 || __atoi(data[1]) > 255)
		ret = false;
	if (__atoi(data[2]) < 0 || __atoi(data[2]) > 255)
		ret = false;
	free_tab(data);
	return (ret);
}
