/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngiroux <ngiroux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 19:12:27 by ngiroux           #+#    #+#             */
/*   Updated: 2023/01/18 17:10:22 by ngiroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef SCENE_H
# define SCENE_H

# include "types.h"
# include "elem.h"

typedef struct s_list
{
	void			*value;
	struct s_list	*next;
}	t_list;

typedef struct s_scene
{
	// t_couple	*res;
	t_ambiant	al;
	t_camera	cam;
	t_list		*lights;
	t_list		*sphere;
	t_list		*plane;
	t_list		*cylinder;
	t_list		*cone;
}	t_scene;

typedef struct s_mlx
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img_ptr;
}	t_mlx;

typedef struct s_minirt
{
	t_scene	*scene;
	t_mlx	*mlx;
}	t_minirt;

#endif /* !SCENE_H */
