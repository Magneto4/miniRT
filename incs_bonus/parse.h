/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngiroux <ngiroux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 16:21:39 by ngiroux           #+#    #+#             */
/*   Updated: 2023/01/16 16:24:49 by ngiroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# define WHITE_SPACE " \t\n"
# define MAX_INT 2147483647
# define MIN_INT -2147483648

// 🏳️ Parse
t_scene	*__parse(char *file);
bool	check_file(char *file);

bool	set_couple(char **data, t_couple *couple);
bool	set_vector(char **data, t_vect *vector);
bool	set_rgb(char **data, t_rgb *rgb);

bool	set_ambiant(char **data, t_scene *scene);
bool	set_camera(char **data, t_scene *scene);
bool	set_light(char **data, t_scene *scene);
bool	set_sphere(char **data, t_scene *scene);
bool	set_plane(char **data, t_scene *scene);
bool	set_cylinder(char **data, t_scene *scene);

bool	check_elem(char **data, t_scene *scene);
bool	check_int(char *str);
bool	check_double(char *str);
bool	check_vector(char *str);
bool	check_vector_norm(char *str);
bool	check_rgb(char *str);
bool	null_vector(char **data);

bool	check_ambiant(char **data);
bool	check_camera(char **data);
bool	check_light(char **data);
bool	check_sphere(char **data);
bool	check_plane(char **data);
bool	check_cylinder(char **data);

void	free_gnl(int fd, char *line);

#endif /* !PARSE_H */