/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngiroux <ngiroux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 14:19:28 by ngiroux           #+#    #+#             */
/*   Updated: 2023/02/03 15:01:31 by ngiroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	check_checkered(char *data)
{
	if (!__strcmp(data, "checkered"))
		return (true);
	return (false);
}

bool	check_xpm(char *data)
{
	if (__strcmp(".xpm", data + __strlen(data) - 4))
		return (false);
	if (check_file(data) == false)
		return (false);
	return (true);
}

bool	check_bonus(char **data)
{
	bool	checkered;
	bool	intensity;
	bool	xpm;
	int		n;

	n = __wordcount(data);
	if (n > 3 || n < 1)
		return (false);
	checkered = false;
	intensity = false;
	xpm = false;
	while (n--)
	{
		if (checkered == false && check_checkered(data[n]) == true)
			checkered = true;
		else if (intensity == false && check_double(data[n]) == true)
			intensity = true;
		else if (xpm == false && check_xpm(data[n]) == true)
			xpm = true;
		else
			return (false);
	}
	return (true);
}
