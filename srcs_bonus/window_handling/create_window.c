/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_window.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseniak <nseniak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 18:45:12 by nseniak           #+#    #+#             */
/*   Updated: 2023/01/17 20:20:48 by nseniak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	init_window(t_minirt *minirt)
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_mlx	*mlx;

	mlx = malloc(sizeof(*mlx));
	if (!mlx)
	{
		free (minirt->scene);
		free (minirt);
		return (1);
	}
	mlx_ptr = mlx_init();
	mlx->mlx_ptr = mlx_ptr;
	win_ptr = mlx_new_window(mlx_ptr, W, H, "miniRT");
	mlx->win_ptr = win_ptr;
	minirt->mlx = mlx;
	return (0);
}

void	start_loop(t_minirt *minirt)
{
	mlx_key_hook(minirt->mlx->win_ptr, key, (void *)minirt);
	mlx_hook(minirt->mlx->win_ptr, 17, 0, close_hook, (void *)minirt);
	mlx_loop(minirt->mlx->mlx_ptr);
}
