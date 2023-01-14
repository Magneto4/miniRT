/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_types.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngiroux <ngiroux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 18:23:25 by ngiroux           #+#    #+#             */
/*   Updated: 2023/01/14 17:28:54 by ngiroux          ###   ########.fr       */
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

	if (!str)
		return (false);
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
	if (!str)
		return (false);
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
	int		i;

	ret = true;
	data = split_set(str, ",");
	if (__wordcount(data) != 3)
		ret = false;
	i = 0;
	while (i < 3 && ret == true)
	{
		if (check_double(data[i]) == false)
			ret = false;
		i++;
	}
	free_tab(data);
	return (ret);
}

bool	check_vector_norm(char *str)
{
	char	**data;
	bool	ret;
	int		i;

	ret = true;
	data = split_set(str, ",");
	if (__wordcount(data) != 3)
		ret = false;
	i = 0;
	while (i < 3 && ret == true)
	{
		if (check_double(data[i]) == false)
			ret = false;
		if (ret == false || __atod(data[i]) < -1 || __atod(data[i]) > 1)
			ret = false;
		i++;
	}
	free_tab(data);
	return (ret);
}

bool	check_rgb(char *str)
{
	char	**data;
	bool	ret;
	int		i;

	ret = true;
	data = split_set(str, ",");
	if (__wordcount(data) != 3)
		ret = false;
	i = 0;
	while (i < 3 && ret == true)
	{
		if (check_int(data[i]) == false)
			ret = false;
		if (ret == false || __atoi(data[i]) < 0 || __atoi(data[i]) > 255)
			ret = false;
		i++;
	}
	free_tab(data);
	return (ret);
}
