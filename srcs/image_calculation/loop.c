/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseniak <nseniak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 18:21:57 by nseniak           #+#    #+#             */
/*   Updated: 2023/01/06 18:45:08 by nseniak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	rgb_to_int(t_rgb rgb)
{
	int	colour;

	if (rgb.r > 255)
		rgb.r = 255;
	if (rgb.g > 255)
		rgb.g = 255;
	if (rgb.b > 255)
		rgb.b = 255;
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

t_vect	x_rot(t_vect v, float a)
{
	t_vect	res;
	double	mat[3][3];

	mat[0][0] = 1;
	mat[0][1] = 0;
	mat[0][2] = 0;
	mat[1][0] = 0;
	mat[1][1] = cos(a);
	mat[1][2] = -sin(a);
	mat[2][0] = 0;
	mat[2][1] = sin(a);
	mat[2][2] = cos(a);
	res = mat_mult(mat, v);
	return (res);
}

t_vect	y_rot(t_vect v, float a)
{
	t_vect	res;
	double	mat[3][3];

	mat[0][0] = cos(a);
	mat[0][1] = 0;
	mat[0][2] = sin(a);
	mat[1][0] = 0;
	mat[1][1] = 1;
	mat[1][2] = 0;
	mat[2][0] = - sin(a);
	mat[2][1] = 0;
	mat[2][2] = cos(a);
	res = mat_mult(mat, v);
	return (res);
}

t_vect	z_rot(t_vect v, float a)
{
	t_vect	res;
	double	mat[3][3];

	mat[0][0] = cos(a);
	mat[0][1] = - sin(a);
	mat[0][2] = 0;
	mat[1][0] = sin(a);
	mat[1][1] = cos(a);
	mat[1][2] = 0;
	mat[2][0] = 0;
	mat[2][1] = 0;
	mat[2][2] = 1;
	res = mat_mult(mat, v);
	return (res);
}

t_vect orientation_vector(t_minirt *minirt, double x, double y)
{
	t_vect	v;

	v.x = (2 * ((x + 0.5) / WIDTH) - 1) * tan(minirt->scene->cam.fov / 2 * M_PI / 180.) * WIDTH / HEIGHT;
	v.y = (1 - 2 * ((y + 0.5) / HEIGHT)) * tan(minirt->scene->cam.fov / 2 * M_PI / 180.);
	v.z = -1;
	normalise(&v);
	if (minirt->scene->cam.dir.x != 0.)
		v = z_rot(v, atan(minirt->scene->cam.dir.y / minirt->scene->cam.dir.x));
	v = y_rot(v, acos(minirt->scene->cam.dir.z) - M_PI);
	return (v);
}

int	generate_pixel(t_minirt *minirt, int x, int y)
{
	t_point	*point;
	t_vect		v;

	v = orientation_vector(minirt, (double)x, (double)y);
	point = calculate_intersection(minirt, v);
	if (point == NULL)
	{
		img_pixel_put(minirt->mlx->img_ptr, x, y, 0xffffff);
		return (0);
	}
	calculate_colour(minirt, point, v);
	img_pixel_put(minirt->mlx->img_ptr, x, y, rgb_to_int(point->lit_colour));
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