/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngiroux <ngiroux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 15:02:27 by ngiroux           #+#    #+#             */
/*   Updated: 2023/02/01 15:42:34 by ngiroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	create_texture(t_mlx *mlx, t_text *text, char *path)
{
	text.ptr = mlx_xpm_file_to_image(mlx->mlx_ptr, path, &text->width, &text->height);
	text.img = mlx_get_data_addr(text.ptr, &text.bpp, &text.size_line, &text.endian);
}

// t_rgb	get_rgb(t_point p)
// {
// 	t_rgb	color;
// 	int		i;
// 	int		column;
// 	int		row;
// 	t_text	text;

// 	i = 0;
// 	column = 0;
// 	row = 0;
// 	if (p.bonus.textured == true)
// 	{
// 		// get_text_coord (rt, rt obj, &column, &row)
// 		text = p.bonus.text;
// 		i = row * text.size_line + text.bpp / 8 * column;
// 		color.r = (int)p.bonus.text.img[i] / 255;
// 		color.g = (int)p.bonus.text.img[i + 1] / 255;
// 		color.b = (int)p.bonus.text.img[i + 2] / 255;
// 	}
// 	else
// 		color = p.color;
// 	return (color);
// }

void	init_bonus(t_bonus *bonus)
{
	bonus->checkered = false;
	bonus->textured = false;
	bonus->n = REFLECT;
}

void	set_bonus(char **data, t_bonus *bonus)
{
	int		n;

	n = __wordcount(data);
	init_bonus(bonus);
	while (n--)
	{
		if (check_checkered(data[n]) == true)
			bonus->checkered = true;
		else if (check_double(data[n]) == true)
			bonus->n = __atod(data[n]);
		else if (check_xpm(data[n]) == true)
		{
			bonus->textured = true;
			// create_texture(mlx, &bonus->text, data[n]);
		}
	}
}
