/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_minirt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngiroux <ngiroux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 16:25:18 by nseniak           #+#    #+#             */
/*   Updated: 2023/01/08 15:20:12 by ngiroux          ###   ########.fr       */
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
	// free(scene);
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
	free(minirt->scene);
	free(minirt);
}
