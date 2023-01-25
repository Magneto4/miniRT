/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngiroux <ngiroux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 13:57:18 by ngiroux           #+#    #+#             */
/*   Updated: 2023/01/25 14:04:51 by ngiroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	check_line(char **data, t_scene *scene)
{
	bool	ret;

	ret = true;
	if (!data[0])
		return (true);
	if (!__strcmp(data[0], "A") && scene->al.ratio != -1)
		return (put_error_false("ambiant light already set"));
	else if (!__strcmp(data[0], "C") && scene->cam.fov != -1)
		return (put_error_false("camera already set"));
	return (ret);
}

bool	set_elem(char *line, t_scene *scene)
{
	char	**data;

	data = split_set(line, WHITE_SPACE);
	if (!data)
		return (put_error_false("mallocing data"));
	if (!data[0])
		return (free_tab(data), true);
	if (data[0][0] == '#')
		return (free_tab(data), true);
	if (check_line(data, scene) == false || check_elem(data, scene) == false)
	{
		free_tab(data);
		free_scene(scene);
		return (put_error_false("parsing line"));
	}
	free_tab(data);
	return (true);
}

bool	set_scene(char *file, t_scene *scene)
{
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (put_error_false("opening file"));
	line = get_next_line(fd);
	while (line)
	{
		if (set_elem(line, scene) == false)
			return (free_gnl(fd, line), false);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if (scene->al.ratio == -1 || scene->cam.fov == -1)
		return (put_error_false("missing ambiant light or camera"), false);
	return (true);
}

void	*init_scene(t_scene *scene)
{
	scene->al.ratio = -1;
	scene->cam.fov = -1;
	scene->lights = NULL;
	scene->sphere = NULL;
	scene->plane = NULL;
	scene->cylinder = NULL;
	scene->cone = NULL;
	return (scene);
}

t_scene	*__parse(char *file)
{
	t_scene	*scene;

	scene = malloc(sizeof(t_scene));
	if (!scene)
		return (put_error_null("mallocing scene"), NULL);
	if (!check_file(file))
		return (NULL);
	scene = init_scene(scene);
	if (set_scene(file, scene) == false)
		return (put_error_null("setting scene"), free(scene), NULL);
	return (scene);
}
