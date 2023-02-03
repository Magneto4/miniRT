/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elem.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngiroux <ngiroux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 17:52:21 by ngiroux           #+#    #+#             */
/*   Updated: 2023/02/01 14:57:27 by ngiroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ELEM_H
# define ELEM_H

# include "types.h"

typedef struct s_ambiant
{
	t_rgb	rgb;
	double	ratio;
}	t_ambiant;

typedef struct s_camera
{
	t_vect	pos;
	t_vect	dir;
	double	fov;
	t_mat	*cam_to_world;
}	t_camera;

typedef struct s_light
{
	t_vect	pos;
	t_rgb	rgb;
	double	ratio;
}	t_light;

typedef struct s_sphere
{
	t_vect	pos;
	double	radius;
	t_rgb	rgb;
	int		checkered;
	t_bonus	bonus;
}	t_sphere;

typedef struct s_plane
{
	t_vect	pos;
	t_vect	dir;
	t_rgb	rgb;
	int		checkered;
	t_bonus	bonus;
}	t_plane;

typedef struct s_cylinder
{
	t_vect	pos;
	t_vect	dir;
	t_vect	top;
	double	radius;
	double	height;
	t_rgb	rgb;
	int		checkered;
	t_vect	def;
	t_bonus	bonus;
}	t_cylinder;

typedef struct s_cone
{
	t_vect	pos;
	t_vect	dir;
	t_vect	top;
	double	radius;
	double	height;
	t_rgb	rgb;
	int		checkered;
	t_bonus	bonus;
}	t_cone;

typedef struct s_point
{
	t_vect	pos;
	t_vect	normal;
	t_rgb	rgb;
	t_rgb	lit_rgb;
	int		init;
	void	*shape;
	double	t;
	t_bonus	bonus;
}	t_point;

#endif /* !ELEM_H */
