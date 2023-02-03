/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngiroux <ngiroux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 15:02:27 by ngiroux           #+#    #+#             */
/*   Updated: 2023/02/03 18:30:29 by ngiroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	create_texture(t_mlx *mlx, t_text *text, char *path)
{
	if (path == NULL)
		return ;
	text->ptr = mlx_xpm_file_to_image(mlx->mlx_ptr, path,
			&text->width, &text->height);
	text->img = mlx_get_data_addr(text->ptr, &text->bpp,
			&text->size_line, &text->endian);
}

t_vect	get_normal2(t_point p, int x, int y)
{
	t_vect	color;
	int		i;
	t_text	texture;

	i = 0;
	color.x = 0;
	color.y = 0;
	color.z = 0;
	if (p.bonus.textured == true)
	{
		texture = p.bonus.text;
		i = x * texture.size_line + texture.bpp / 8 * y;
		color.z = (double)(unsigned char)texture.img[i] / 255;
		color.y = (double)(unsigned char)texture.img[i + 1] / 255;
		color.x = (double)(unsigned char)texture.img[i + 2] / 255;
	}
	return (color);
}

void	init_bonus(t_bonus *bonus)
{
	bonus->checkered = false;
	bonus->textured = false;
	bonus->n = REFLECT;
	bonus->text.ptr = NULL;
	bonus->text.img = NULL;
}

void	set_bonus(t_mlx *mlx, char **data, t_bonus *bonus)
{
	int		n;

	init_bonus(bonus);
	n = __wordcount(data);
	if (n == 0)
		return ;
	while (n--)
	{
		if (check_checkered(data[n]) == true)
			bonus->checkered = true;
		else if (check_double_mute(data[n]) == true)
			bonus->n = __atod(data[n]);
		else if (check_xpm(data[n]) == true)
		{
			bonus->textured = true;
			create_texture(mlx, &bonus->text, data[n]);
		}
	}
}
