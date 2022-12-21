/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseniak <nseniak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 18:36:44 by nseniak           #+#    #+#             */
/*   Updated: 2022/12/21 20:08:15 by nseniak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	clean_end(t_minirt *minirt)
{
	// mlx_destroy_image(minirt->mlx->mlx_ptr, minirt->mlx->img_ptr);
	mlx_loop_end(minirt->mlx->mlx_ptr);
	mlx_destroy_window(minirt->mlx->mlx_ptr, minirt->mlx->win_ptr);
	mlx_destroy_display(minirt->mlx->mlx_ptr);
	free(minirt->mlx->mlx_ptr);
	free(minirt->mlx);
	free(minirt->scene);
	free(minirt);
}

int	key(int keycode, void *void_minirt)
{
	t_minirt	*minirt;

	minirt = (t_minirt *)void_minirt;
	if (keycode == 65307)
	{
		clean_end(minirt);
		exit (0);
	}
	return (0);
}

int	close_hook(void *void_minirt)
{
	t_minirt	*minirt;

	minirt = (t_minirt *)void_minirt;
	clean_end(minirt);
	exit (0);
}
