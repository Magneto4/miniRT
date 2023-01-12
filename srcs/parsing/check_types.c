/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_types.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngiroux <ngiroux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 18:23:25 by ngiroux           #+#    #+#             */
/*   Updated: 2023/01/12 17:31:57 by ngiroux          ###   ########.fr       */
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
