/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseniak <nseniak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 19:04:18 by ngiroux           #+#    #+#             */
/*   Updated: 2023/01/25 20:31:39 by nseniak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

typedef struct s_couple
{
	int		x;
	int		y;
}	t_couple;

typedef struct s_vect
{
	double	x;
	double	y;
	double	z;
}	t_vect;

typedef struct s_vect2
{
	double	u;
	double	v;
}	t_vect2;

typedef struct s_rgb
{
	int		r;
	int		g;
	int		b;
}	t_rgb;

typedef struct s_ray
{
	t_vect	src;
	t_vect	dir;
}	t_ray;

typedef struct s_xpm
{
	int		width;
	int		height;
	int		*data;
}	t_xpm;

typedef struct s_bonus
{
	bool	checkered;
	double	n;
	t_xpm	*xpm;
}	t_bonus;

typedef double	t_mat[3][3];

#endif /* !TYPES_H */
