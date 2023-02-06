/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngiroux <ngiroux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 19:32:53 by ngiroux           #+#    #+#             */
/*   Updated: 2023/02/06 17:41:26 by ngiroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	null_vector(char **data)
{
	if (__atod(data[0]) == 0 && __atod(data[1]) == 0 && __atod(data[2]) == 0)
		return (false);
	return (true);
}

bool	check_file(char *file)
{
	int	fd;

	fd = open(file, O_DIRECTORY);
	if (fd > 0)
	{
		close(fd);
		return (put_error_false("it's a directory"));
	}
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (put_error_false("opening file"));
	close(fd);
	return (true);
}
