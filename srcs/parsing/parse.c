/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngiroux <ngiroux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 13:57:18 by ngiroux           #+#    #+#             */
/*   Updated: 2023/01/09 16:50:17 by ngiroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	set_elem(char *line, t_scene *scene)
{
	char	**data;
	// char	**tmp;

	data = split_set(line, WHITE_SPACE);
	// tmp = data;
	// while (*tmp)
	// {
	// 	printf("data: %s\n", *tmp);
	// 	tmp++;
	// }
	if (!data)
		return (put_error_null("Error mallocing data"));
	if (!__strcmp(data[0], "A"))
		set_ambiant(data, scene);
	else if (!__strcmp(data[0], "C"))
		set_camera(data, scene);
	else if (!__strcmp(data[0], "L"))
		set_light(data, scene);
	else if (!__strcmp(data[0], "sp"))
		set_sphere(data, scene);
	else if (!__strcmp(data[0], "pl"))
		set_plane(data, scene);
	else if (!__strcmp(data[0], "cy"))
		set_cylinder(data, scene);
	else
		return (free_tab(data), put_error_null("Error unknown identifier"));
	free_tab(data);
}

void	set_scene(char *file, t_scene *scene)
{
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (put_error_null("Error opening file"));
	line = get_next_line(fd);
	while (line)
	{
		set_elem(line, scene);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}

void	*init_scene(t_scene *scene)
{
	// scene->al = NULL;
	// scene->cam = NULL;
	scene->lights = NULL;
	scene->sphere = NULL;
	scene->plane = NULL;
	scene->cylinder = NULL;
	return (scene);
}

bool	check_file(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (put_error_false("Error opening file"));
	close(fd);
	return (true);
}

t_scene	*__parse(char *file)
{
	t_scene	*scene;

	scene = malloc(sizeof(t_scene));
	if (!scene)
		return (put_error_null("Error mallocing scene"), NULL);
	if (!check_file(file))
		return (put_error_null("Error in file"), NULL);
	scene = init_scene(scene);
	set_scene(file, scene);
	if (!scene)
		return (free(scene), NULL);
	return (scene);
}
