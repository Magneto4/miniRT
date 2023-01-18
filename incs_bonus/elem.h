/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elem.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseniak <nseniak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 17:52:21 by ngiroux           #+#    #+#             */
/*   Updated: 2023/01/18 15:21:34 by nseniak          ###   ########.fr       */
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
	double	n;
	int		checkered;
}	t_sphere;

typedef struct s_plane
{
	t_vect	pos;
	t_vect	dir;
	t_rgb	rgb;
	double	n;
	int		checkered;
}	t_plane;

typedef struct s_cylinder
{
	t_vect	pos;
	t_vect	dir;
	t_vect	top;
	double	radius;
	double	height;
	t_rgb	rgb;
	double	n;
	int		checkered;
}	t_cylinder;

#endif /* !ELEM_H */
