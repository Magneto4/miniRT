/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_types.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngiroux <ngiroux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 18:23:25 by ngiroux           #+#    #+#             */
/*   Updated: 2023/01/14 18:50:53 by ngiroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
				return (put_error_false("invalid double"));
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
			return (put_error_false("invalid int"));
		str++;
	}
	return (true);
}

bool	check_vector(char *str)
{
	char	**data;
	bool	ret;
	int		i;

	data = split_set(str, ",");
	if (__wordcount(data) != 3)
		return (free_tab(data), put_error_false("invalid vector"));
	i = 0;
	ret = true;
	while (i < 3 && ret == true)
	{
		if (check_double(data[i]) == false)
			ret = false;
		i++;
	}
	free_tab(data);
	if (ret == false)
		return (put_error_false("invalid vector"));
	return (ret);
}

bool	check_vector_norm(char *str)
{
	char	**data;
	bool	ret;
	int		i;

	data = split_set(str, ",");
	if (__wordcount(data) != 3)
		return (free_tab(data), put_error_false("invalid vector"));
	i = 0;
	ret = true;
	while (i < 3 && ret == true)
	{
		if (check_double(data[i]) == false)
			ret = false;
		if (ret == false || __atod(data[i]) < -1 || __atod(data[i]) > 1)
			ret = false;
		i++;
	}
	if (ret == true && __atod(data[0]) == 0 && __atod(data[1]) == 0 && __atod(data[2]) == 0)
		ret = false;
	free_tab(data);
	if (ret == false)
		return (put_error_false("invalid vector"));
	return (ret);
}

bool	check_rgb(char *str)
{
	char	**data;
	bool	ret;
	int		i;

	data = split_set(str, ",");
	if (__wordcount(data) != 3)
		return (free_tab(data), put_error_false("invalid rgb"));
	i = 0;
	ret = true;
	while (i < 3 && ret == true)
	{
		if (check_int(data[i]) == false)
			ret = false;
		if (ret == false || __atoi(data[i]) < 0 || __atoi(data[i]) > 255)
			ret = false;
		i++;
	}
	free_tab(data);
	if (ret == false)
		return (put_error_false("invalid rgb"));
	return (ret);
}
