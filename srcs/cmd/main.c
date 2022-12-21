/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngiroux <ngiroux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 13:51:06 by ngiroux           #+#    #+#             */
/*   Updated: 2022/12/20 17:22:32 by ngiroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	main(int ac, char **av)
{
	t_scene	*scene;

	if (ac != 2 || __strcmp(".rt", av[1] + __strlen(av[1]) - 3))
		return (put_error("Usage: ./miniRT <file.rt>"));
	scene = __parse(av[1]);
	if (!scene)
		return (EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}
