/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseniak <nseniak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 13:39:52 by ngiroux           #+#    #+#             */
/*   Updated: 2022/12/22 22:41:37 by nseniak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

// 🎩 Includes
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include <stdio.h>
# include <stdbool.h>
# include <fcntl.h>

# include "scene.h"
# include "types.h"
# include "elem.h"
# include "../mlx/mlx.h"

// 🕵️‍♂️ Define
# define HEIGHT 500
# define F_HEIGHT 500.
# define WIDTH 500
# define F_WIDTH 500.
# define PI 3.141592653589793

// 🏳️ Parse
t_scene	*__parse(char *file);

// 🏔️ MiniRT

// 🧰 Utils
int		put_error(char *str);
void	put_error_null(char *str);
bool	put_error_false(char *str);

// 📚 Libs
int		__strlen(char *str);
int		__strcmp(const char *s1, const char *s2);

//window
int		init_window(t_minirt *minirt);
void	start_loop(t_minirt *minirt);
int		close_hook(void *void_minirt);
int		key(int keycode, void *void_minirt);
void	clean_end(t_minirt *minirt);

//image
int		create_image(t_minirt *minirt);
t_point	*calculate_intersection(t_minirt *minirt, int x, int y);
int		calculate_colour(t_minirt *minirt, t_point *point);
void	normalise(t_vect *v);
t_point	*closest_sphere(t_minirt *minirt, t_vect *v);
t_point	*closest_cylinder(t_minirt *minirt, t_vect *v);
t_point	*closest_plane(t_minirt *minirt, t_vect *v);
double	distance(t_vect *a, t_vect *b);

#endif /* MINIRT_H */
