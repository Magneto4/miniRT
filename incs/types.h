/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngiroux <ngiroux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 19:04:18 by ngiroux           #+#    #+#             */
/*   Updated: 2022/12/20 19:10:03 by ngiroux          ###   ########.fr       */
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

#endif /* !TYPES_H */
