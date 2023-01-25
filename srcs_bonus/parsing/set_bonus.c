/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngiroux <ngiroux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 15:02:27 by ngiroux           #+#    #+#             */
/*   Updated: 2023/01/25 15:41:16 by ngiroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	init_bonus(t_bonus *bonus)
{
	bonus->checkered = false;
	bonus->n = 1;
	bonus->xpm = NULL;
}

void	set_bonus(char **data, t_bonus *bonus)
{
	int		n;

	n = __wordcount(data);
	init_bonus(bonus);
	while (n--)
	{
		if (check_checkered(data[n]) == true)
			bonus->checkered = true;
		else if (check_double(data[n]) == true)
			bonus->n = __atod(data[n]);
		else if (check_xpm(data[n]) == true)
			bonus->xpm = NULL;
	}
}
