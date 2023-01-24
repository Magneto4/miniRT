/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseniak <nseniak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 18:21:57 by nseniak           #+#    #+#             */
/*   Updated: 2023/01/24 14:21:03 by nseniak          ###   ########.fr       */
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

t_vect	x_rot(t_vect v, double a)
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

t_vect	y_rot(t_vect v, double a)
{
	t_vect	res;
	double	mat[3][3];

	mat[0][0] = cos(a);
	mat[0][1] = 0;
	mat[0][2] = sin(a);
	mat[1][0] = 0;
	mat[1][1] = 1;
	mat[1][2] = 0;
	mat[2][0] = -sin(a);
	mat[2][1] = 0;
	mat[2][2] = cos(a);
	res = mat_mult(mat, v);
	return (res);
}

t_vect	z_rot(t_vect v, double a)
{
	t_vect	res;
	double	mat[3][3];

	mat[0][0] = cos(a);
	mat[0][1] = -sin(a);
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


t_vect	orientation_vect(t_camera cam, double x, double y)
{
	t_vect	v;

	v.x = (2 * ((x + 0.5) / W) - 1) * tan(cam.fov / 2 * M_PI / 180.) * W / H;
	v.y = (1 - 2 * ((y + 0.5) / H)) * tan(cam.fov / 2 * M_PI / 180.);
	v.z = -1;
	normalise(&v);
	v = mat_mult(*(cam.cam_to_world), v);
	return (v);
}

int	generate_pixel(t_minirt *minirt, int x, int y)
{
	t_point	*point;
	t_ray	ray;
	int		colour;

	ray.dir = orientation_vect(minirt->scene->cam, (double)x, (double)y);
	ray.src = minirt->scene->cam.pos;
	point = calculate_intersection(minirt, ray);
	if (point->init == 0)
		colour = 0x000000;
	else
	{
		calculate_colour(minirt, point, ray.dir);
		colour = rgb_to_int(point->lit_rgb);
	}
	img_pixel_put(minirt->mlx->img_ptr, x, y, colour);
	free(point);
	return (0);
}

void	create_cam_to_world(t_camera cam)
{
	t_vect	right;
	t_vect	up;
	t_mat	world_to_cam;

	up = init_vector(0, 1, 0);
	right = cross(up, cam.dir);
	normalise(&right);
	up = cross(cam.dir, right);
	normalise(&up);
	world_to_cam[0][0] = right.x;
	world_to_cam[1][0] = right.y;
	world_to_cam[2][0] = right.z;
	world_to_cam[0][1] = up.x;
	world_to_cam[1][1] = up.y;
	world_to_cam[2][1] = up.z;
	world_to_cam[0][2] = - 1 * cam.dir.x;
	world_to_cam[1][2] = -1 * cam.dir.y;
	world_to_cam[2][2] = -1 * cam.dir.z;
	invert(world_to_cam, cam.cam_to_world);
}

int	create_image(t_minirt *minirt)
{
	int		x;
	int		y;
	void	*img_ptr;
	t_mlx	*mlx;

	mlx = minirt->mlx;
	img_ptr = mlx_new_image(mlx->mlx_ptr, W, H);
	mlx->img_ptr = img_ptr;
	minirt->scene->cam.cam_to_world = malloc(sizeof(*(minirt->scene->cam.cam_to_world)));
	if (!(minirt->scene->cam.cam_to_world))
		clean_end(minirt);
	create_cam_to_world(minirt->scene->cam);
	x = 0;
	while (x < W)
	{
		y = 0;
		while (y < H)
		{
			if (generate_pixel(minirt, x, y))
				return (1);
			y ++;
		}
		x ++;
	}
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, img_ptr, 0, 0);
	return (0);
}
