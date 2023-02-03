/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_minirt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseniak <nseniak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 16:25:18 by nseniak           #+#    #+#             */
/*   Updated: 2023/02/03 16:37:59 by nseniak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	__del(void *ptr)
{
	free (ptr);
}

void	free_scene(t_scene *scene)
{
	__lstclear(&(scene->cylinder), __del);
	if (scene->cylinder)
		free(scene->cylinder);
	__lstclear(&(scene->lights), __del);
	if (scene->lights)
		free(scene->lights);
	__lstclear(&(scene->plane), __del);
	if (scene->plane)
		free(scene->plane);
	__lstclear(&(scene->sphere), __del);
	if (scene->sphere)
		free(scene->sphere);
	__lstclear(&(scene->cone), __del);
	if (scene->cone)
		free(scene->cone);
	scene = NULL;
}

void	free_minirt(t_minirt *minirt)
{
	free(minirt->mlx->mlx_ptr);
	free(minirt->mlx);
	__lstclear(&(minirt->scene->cylinder), __del);
	if (minirt->scene->cylinder)
		free(minirt->scene->cylinder);
	__lstclear(&(minirt->scene->lights), __del);
	if (minirt->scene->lights)
		free(minirt->scene->lights);
	__lstclear(&(minirt->scene->plane), __del);
	if (minirt->scene->plane)
		free(minirt->scene->plane);
	__lstclear(&(minirt->scene->sphere), __del);
	if (minirt->scene->sphere)
		free(minirt->scene->sphere);
	__lstclear(&(minirt->scene->cone), __del);
	if (minirt->scene->cone)
		free(minirt->scene->cone);
	free(minirt->scene->cam.cam_to_world);
	free(minirt->scene);
	free(minirt);
}

void	free_tab(char **tab)
{
	char	**tmp;

	tmp = tab;
	while (*tmp)
	{
		free(*tmp);
		tmp++;
	}
	free(tab);
}

void	free_gnl(int fd, char *line)
{
	free(line);
	close(fd);
}
