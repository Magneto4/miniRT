/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngiroux <ngiroux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 13:51:06 by ngiroux           #+#    #+#             */
/*   Updated: 2023/02/03 19:14:36 by ngiroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// void	normalise_lights(t_minirt *minirt)
// {
// 	double	total;
// 	t_light	*light;
// 	t_list	*tmp;

// 	total = minirt->scene->al.ratio;
// 	tmp = minirt->scene->lights;
// 	while (tmp)
// 	{
// 		light = (t_light *)(tmp->value);
// 		total += light->ratio;
// 		tmp = tmp->next;
// 	}
// 	if (total <= 1)
// 		return ;
// 	tmp = minirt->scene->lights;
// 	while (tmp)
// 	{
// 		light = (t_light *)(tmp->value);
// 		light->ratio /= total;
// 		tmp = tmp->next;
// 	}
// }

int	main(int ac, char **av)
{
	t_minirt	*minirt;

	if (ac != 2 || __strcmp(".rt", av[1] + __strlen(av[1]) - 3))
		return (put_error("Usage: ./miniRT <file.rt>"));
	minirt = malloc (sizeof(*minirt));
	if (!minirt)
		return (put_error("malloc failure"), 1);
	if (init_mlx(minirt))
		return (put_error("mlx failure"), EXIT_FAILURE);
	minirt->scene = __parse(av[1], minirt->mlx);
	if (!(minirt->scene))
		return (free(minirt), put_error("parse error"), EXIT_FAILURE);
	init_window(minirt->mlx);
	if (create_image(minirt))
	{
		put_error("image failure");
		clean_end(minirt);
	}
	start_loop(minirt);
	return (EXIT_SUCCESS);
}
