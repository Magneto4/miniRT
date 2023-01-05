/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseniak <nseniak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 13:39:52 by ngiroux           #+#    #+#             */
/*   Updated: 2023/01/05 19:54:09 by nseniak          ###   ########.fr       */
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
# define WIDTH 1000

// 🏳️ Parse
t_scene	*__parse(char *file);

// 🏔️ MiniRT

// 🧰 Utils
int		put_error(char *str);
void	put_error_null(char *str);
bool	put_error_false(char *str);
void	free_minirt(t_minirt *minirt);

// 📚 Libs
int		__strlen(char *str);
int		__strcmp(const char *s1, const char *s2);
void	__lstclear(t_list **lst, void (*del)(void *));

//window
int		init_window(t_minirt *minirt);
void	start_loop(t_minirt *minirt);
int		close_hook(void *void_minirt);
int		key(int keycode, void *void_minirt);
void	clean_end(t_minirt *minirt);

//image
int		create_image(t_minirt *minirt);
t_point	*calculate_intersection(t_minirt *minirt, t_vect v);
int		calculate_colour(t_minirt *minirt, t_point *point, t_vect v);
void	normalise(t_vect *v);
void	closest_sphere(t_minirt *minirt, t_vect v, t_point *closest);
void	closest_cylinder(t_minirt *minirt, t_vect v, t_point *closest);
void	closest_plane(t_minirt *minirt, t_vect v, t_point *closest);
double	distance(t_vect a, t_vect b);
t_point	*create_point();
void	free_point(t_point *point);
double	dot(t_vect a, t_vect b);
t_vect	sub(t_vect a, t_vect b);
double	norm(t_vect v);

#endif /* MINIRT_H */
