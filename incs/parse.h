/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngiroux <ngiroux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 16:21:39 by ngiroux           #+#    #+#             */
/*   Updated: 2023/01/14 17:34:45 by ngiroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# define WHITE_SPACE " \t\n"
# define MAX_INT 2147483647
# define MIN_INT -2147483648

// 🏳️ Parse
t_scene	*__parse(char *file);

bool	set_couple(char **data, t_couple *couple);
bool	set_vector(char **data, t_vect *vector);
bool	set_rgb(char **data, t_rgb *rgb);

bool	set_ambiant(char **data, t_scene *scene);
void	set_camera(char **data, t_scene *scene);
void	set_light(char **data, t_scene *scene);
void	set_sphere(char **data, t_scene *scene);
void	set_plane(char **data, t_scene *scene);
void	set_cylinder(char **data, t_scene *scene);

bool	check_double(char *str);
bool	check_int(char *str);
bool	check_vector(char *str);
bool	check_vector_norm(char *str);
bool	check_rgb(char *str);

bool	check_ambiant(char **data);
bool	check_camera(char **data);

void	free_gnl(int fd, char *line);

#endif /* !PARSE_H */