/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseniak <nseniak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 13:51:06 by ngiroux           #+#    #+#             */
/*   Updated: 2022/12/22 19:55:08 by nseniak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_scene	*create_scene()
{
	t_scene	*scene;

	scene = malloc (sizeof(*scene));
	scene->cylinder = NULL;
	scene->sphere = NULL;
	scene->lights = NULL;
	scene->plane = NULL;
	scene->cam = malloc(sizeof(*(scene->cam)));
	scene->cam->dir = malloc(sizeof(*(scene->cam->dir)));
	scene->cam->dir->x = 0;
	scene->cam->dir->y = 0;
	scene->cam->dir->z = 0;
	scene->cam->fov = 180;
	scene->cam->pos = malloc(sizeof(*(scene->cam->pos)));
	scene->cam->pos->x = 0;
	scene->cam->pos->y = 0;
	scene->cam->pos->z = 0;
	return (scene);
}

int	main(int ac, char **av)
{
	t_minirt	*minirt;

	if (ac != 2 || __strcmp(".rt", av[1] + __strlen(av[1]) - 3))
		return (put_error("Usage: ./miniRT <file.rt>"));
	minirt = malloc (sizeof(*minirt));
	if (!minirt)
		return (put_error("malloc failure"), 1);
	// minirt->scene = __parse(av[1]);
	minirt->scene = create_scene();
	if (!(minirt->scene))
		return (free(minirt), put_error("malloc failure"), EXIT_SUCCESS);
	if (init_window(minirt))
		return (put_error("malloc failure"), EXIT_SUCCESS);
	//here we create the image and put it on the screen
	if (create_image(minirt))
	{
		put_error("malloc failure");
		clean_end(minirt);
	}
	start_loop(minirt);
	return (EXIT_SUCCESS);
}
