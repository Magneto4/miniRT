/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseniak <nseniak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 18:21:57 by nseniak           #+#    #+#             */
/*   Updated: 2023/01/04 16:17:00 by nseniak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	rgb_to_int(t_rgb rgb)
{
	int	colour;

	colour = rgb.r * 256 * 256;
	colour += rgb.g * 256;
	colour += rgb.b;
	return (colour);
}

void	img_pixel_put(void *img_ptr, int x, int y, int color)
{
	void	*data;
	void	*pixel;
	int		bpp;
	int		size_line;
	int		endian;

	data = mlx_get_data_addr(img_ptr, &bpp, &size_line, &endian);
	pixel = data + y * size_line + x * bpp / 8;
	*(int *) pixel = color;
}

int	generate_pixel(t_minirt *minirt, int x, int y)
{
	t_point	*point;

	point = calculate_intersection(minirt, x, y);
	if (point == NULL)
	{
		img_pixel_put(minirt->mlx->img_ptr, x, y, 0xffffff);
		return (0);
	}
	calculate_colour(minirt, point);
	img_pixel_put(minirt->mlx->img_ptr, x, y, rgb_to_int(point->lit_colour));
	// free_point(point);
	free(point);
	return (0);
}

int	create_image(t_minirt *minirt)
{
	int		x;
	int		y;
	void	*img_ptr;

	img_ptr = mlx_new_image(minirt->mlx->mlx_ptr, WIDTH, HEIGHT);
	minirt->mlx->img_ptr = img_ptr;
	x = 0;
	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT)
		{
			if (generate_pixel(minirt, x, y))
				return (1);
			y ++;
		}
		x ++;
	}
	(void)minirt;
	mlx_put_image_to_window(minirt->mlx->mlx_ptr, minirt->mlx->win_ptr, img_ptr, 0, 0);
	return (0);
}
