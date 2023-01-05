/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseniak <nseniak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 13:51:06 by ngiroux           #+#    #+#             */
/*   Updated: 2023/01/05 20:31:05 by nseniak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_scene	*create_scene()
{
	t_scene	*scene;
	t_sphere	*sphere;
	t_list		*lst_sphere;

	scene = malloc (sizeof(*scene));
	//adding shapes
	scene->cylinder = NULL;
	sphere = malloc(sizeof(*sphere));
	sphere->pos.x = 6;
	sphere->pos.y = 0;
	sphere->pos.z = -10;
	sphere->radius = 4;
	sphere->rgb.b = 150;
	sphere->rgb.r = 50;
	sphere->rgb.g = 0;
	lst_sphere = malloc(sizeof(*(lst_sphere)));
	lst_sphere->value = (void *)sphere;
	lst_sphere->next = NULL;
	// lst_sphere->next = malloc(sizeof(*(lst_sphere)));
	// lst_sphere->next->next = NULL;
	// sphere = malloc(sizeof(*sphere));
	// sphere->pos.x = 3;
	// sphere->pos.y = 0;
	// sphere->pos.z = -4;
	// sphere->radius = 1;
	// sphere->rgb.b = 0;
	// sphere->rgb.r = 250;
	// sphere->rgb.g = 50;
	// lst_sphere->next->value = sphere;
	scene->sphere = lst_sphere;
	scene->plane = NULL;
	scene->cylinder = NULL;
	//adding lights
	scene->al.ratio = 0;
	scene->al.rgb.r = 255;
	scene->al.rgb.g = 255;
	scene->al.rgb.b = 255;
	scene->lights = malloc(sizeof(*(scene->lights)));
	t_light	*light;
	light = malloc(sizeof(*light));
	light->pos.x = 5;
	light->pos.y = 0;
	light->pos.z = 0;
	light->ratio = 1;
	light->rgb.r = 255;
	light->rgb.g = 255;
	light->rgb.b = 255;
	scene->lights->value = (void *)light;
	scene->lights->next = NULL;
	//adding camra
	scene->cam.dir.x = 0;
	scene->cam.dir.y = 0;
	scene->cam.dir.z = -1;
	scene->cam.fov = 70;
	scene->cam.pos.x = 0;
	scene->cam.pos.y = 0;
	scene->cam.pos.z = 0;
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
