/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseniak <nseniak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 19:04:18 by ngiroux           #+#    #+#             */
/*   Updated: 2023/01/12 14:57:35 by nseniak          ###   ########.fr       */
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

typedef struct s_rgb
{
	int		r;
	int		g;
	int		b;
}	t_rgb;

typedef struct s_point
{
	t_vect	pos;
	t_vect	normal;
	t_rgb	raw_colour;
	t_rgb	lit_colour;
	int		init;
	void	*shape;
}	t_point;

typedef	struct s_ray
{
	t_vect	src;
	t_vect	dir;
}	t_ray;


typedef double t_mat[3][3];

#endif /* !TYPES_H */
