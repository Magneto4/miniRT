/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_elem.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngiroux <ngiroux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 12:57:05 by ngiroux           #+#    #+#             */
/*   Updated: 2023/01/12 18:19:31 by ngiroux          ###   ########.fr       */
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
	return (true);
}
