/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngiroux <ngiroux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 16:21:39 by ngiroux           #+#    #+#             */
/*   Updated: 2023/02/03 15:41:06 by ngiroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# define WHITE_SPACE " \t\n"
# define MAX_INT 2147483647
# define MIN_INT -2147483648

// 🏳️ Parse
t_scene	*__parse(char *file, t_mlx *mlx);
bool	check_file(char *file);

bool	set_couple(char **data, t_couple *couple);
bool	set_vector(char **data, t_vect *vector);
bool	set_rgb(char **data, t_rgb *rgb);

bool	set_ambiant(char **data, t_scene *scene);
bool	set_camera(char **data, t_scene *scene);
bool	set_light(char **data, t_scene *scene);
bool	set_sphere(char **data, t_scene *scene, t_mlx *mlx);
bool	set_plane(char **data, t_scene *scen, t_mlx *mlxe);
bool	set_cylinder(char **data, t_scene *scene, t_mlx *mlx);
bool	set_cone(char **data, t_scene *scene, t_mlx *mlx);

bool	check_elem(char **data, t_scene *scene, t_mlx *mlx);
bool	check_int(char *str);
bool	check_double(char *str);
bool	check_vector(char *str);
bool	check_vector_norm(char *str);
bool	check_rgb(char *str);
bool	null_vector(char **data);

bool	check_checkered(char *data);
bool	check_xpm(char *data);
bool	check_bonus(char **data);

void	init_bonus(t_bonus *bonus);
void	set_bonus(t_mlx *mlx, char **data, t_bonus *bonus);

bool	check_ambiant(char **data);
bool	check_camera(char **data);
bool	check_light(char **data);
bool	check_sphere(char **data);
bool	check_plane(char **data);
bool	check_cylinder(char **data);

void	free_gnl(int fd, char *line);

#endif /* !PARSE_H */