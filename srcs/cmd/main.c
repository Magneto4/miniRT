/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseniak <nseniak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 13:51:06 by ngiroux           #+#    #+#             */
/*   Updated: 2022/12/21 19:06:48 by nseniak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	main(int ac, char **av)
{
	t_minirt	*minirt;

	if (ac != 2 || __strcmp(".rt", av[1] + __strlen(av[1]) - 3))
		return (put_error("Usage: ./miniRT <file.rt>"));
	minirt = malloc (sizeof(*minirt));
	if (!minirt)
		return (put_error("malloc failure"), 1);
	minirt->scene = __parse(av[1]);
	if (!(minirt->scene))
		return (free(minirt), put_error("malloc failure"), EXIT_SUCCESS);
	if (init_window(minirt))
		return (put_error("malloc failure"), EXIT_SUCCESS);
	//here we create the image and put it on the screen
	start_loop(minirt);
	return (EXIT_SUCCESS);
}
