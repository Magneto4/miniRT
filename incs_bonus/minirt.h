/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseniak <nseniak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 13:39:52 by ngiroux           #+#    #+#             */
/*   Updated: 2023/01/18 18:04:34 by nseniak          ###   ########.fr       */
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

# include "get_next_line.h"
# include "scene.h"
# include "types.h"
# include "elem.h"
# include "../mlx/mlx.h"

# include "parse.h"

// 🕵️‍♂️ Define
# define H 900.
# define W 1500.

# define SP 1
# define CY 2
# define PL 3
# define EPSILON 0.0001

# ifndef BONUS
#  define BONUS 1
# endif

// 🏔️ MiniRT

// 🧰 Utils
int		put_error(char *str);
void	put_error_null(char *str);
bool	put_error_false(char *str);
void	free_minirt(t_minirt *minirt);
void	free_scene(t_scene *scene);
void	free_tab(char **tab);
int		__wordcount(char **line);
int		wordcount_set(char *str, char *sep);

// 📚 Libs
int		__strlen(char *str);
int		__strcmp(const char *s1, const char *s2);
void	__lstclear(t_list **lst, void (*del)(void *));
void	__lstdelone(t_list *lst, void (*del)(void *));
void	__lstadd_front(t_list **lst, t_list *new);
t_list	*__lstnew(void *content);

int		__atoi(char *str);
double	__atod(char *str);
char	**split_set(char *s, char *charset);

//window
int		init_window(t_minirt *minirt);
void	start_loop(t_minirt *minirt);
int		close_hook(void *void_minirt);
int		key(int keycode, void *void_minirt);
void	clean_end(t_minirt *minirt);

//image
int		create_image(t_minirt *minirt);
t_point	*calculate_intersection(t_minirt *minirt, t_ray ray);
int		calculate_colour(t_minirt *minirt, t_point *point, t_vect v);
void	normalise(t_vect *v);
void	closest_sphere(t_minirt *minirt, t_ray ray, t_point *closest);
void	closest_cylinder(t_minirt *minirt, t_ray ray, t_point *closest);
void	closest_plane(t_minirt *minirt, t_ray ray, t_point *closest);
double	distance(t_vect a, t_vect b);
t_point	*create_point();
void	free_point(t_point *point);
double	dot(t_vect a, t_vect b);
t_vect	sub(t_vect a, t_vect b);
double	norm(t_vect v);
t_vect	mat_mult(double mat[3][3], t_vect v);
int	solve_quadratic(t_vect v, double *x1, double *x2);
t_vect	cross(t_vect v, t_vect w);
t_vect	add(t_vect a, t_vect b);
t_vect	mult(t_vect v, double a);
void	plane_inter(t_ray ray, t_plane *plane, t_point *closest);
t_vect	plane_normal(t_plane *plane, t_vect src, t_vect inter);
int		in_cyl(t_cylinder *cyl, t_vect pos);
int		shaded(t_minirt *minirt, t_ray ray, void *shape);

#endif /* MINIRT_H */
