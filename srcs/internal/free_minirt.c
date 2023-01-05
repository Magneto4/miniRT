/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_minirt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseniak <nseniak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 16:25:18 by nseniak           #+#    #+#             */
/*   Updated: 2023/01/05 17:29:45 by nseniak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	__del(void *ptr)
{
	free (ptr);
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
