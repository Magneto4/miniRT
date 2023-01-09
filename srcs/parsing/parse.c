/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngiroux <ngiroux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 13:57:18 by ngiroux           #+#    #+#             */
/*   Updated: 2023/01/08 16:59:27 by ngiroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// make atof

void	set_scene(char *file, t_scene *scene)
{
	int		fd;
	char	*line;
	int		ret;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (put_error_null("Error opening file"));
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		free(line);
	}
	if (ret == -1)
		return (put_error_null("Error reading file"));
	close(fd);
}

void	*init_scene(t_scene *scene)
{
	// scene->al = NULL;
	// scene->cam = NULL;
	scene->lights = __lstnew(NULL);
	scene->sphere = __lstnew(NULL);
	scene->plane = __lstnew(NULL);
	scene->cylinder = __lstnew(NULL);
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
