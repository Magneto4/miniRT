/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngiroux <ngiroux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 17:10:36 by ngiroux           #+#    #+#             */
/*   Updated: 2023/02/03 19:09:04 by ngiroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	free_bonus(t_scene *scene, t_mlx *mlx)
{
	del_sphere(scene->sphere, mlx);
	del_cylinder(scene->cylinder, mlx);
	del_plane(scene->plane, mlx);
	del_cone(scene->cone, mlx);
}

void	del_sphere(t_list *lst, t_mlx *mlx)
{
	t_sphere	*sphere;

	if (!lst)
		return ;
	while (lst != NULL)
	{
		sphere = (t_sphere *)lst->value;
		if (sphere->bonus.textured && sphere->bonus.text.ptr)
			mlx_destroy_image(mlx->mlx_ptr, sphere->bonus.text.ptr);
		lst = lst->next;
	}
}

void	del_cylinder(t_list *lst, t_mlx *mlx)
{
	t_cylinder	*cylinder;

	if (!lst)
		return ;
	while (lst != NULL)
	{
		cylinder = (t_cylinder *)lst->value;
		if (cylinder->bonus.textured && cylinder->bonus.text.ptr)
			mlx_destroy_image(mlx->mlx_ptr, cylinder->bonus.text.ptr);
		lst = lst->next;
	}
}

void	del_plane(t_list *lst, t_mlx *mlx)
{
	t_plane	*plane;

	if (!lst)
		return ;
	while (lst != NULL)
	{
		plane = (t_plane *)lst->value;
		if (plane->bonus.textured && plane->bonus.text.ptr)
			mlx_destroy_image(mlx->mlx_ptr, plane->bonus.text.ptr);
		lst = lst->next;
	}
}

void	del_cone(t_list *lst, t_mlx *mlx)
{
	t_cone	*cone;

	if (!lst)
		return ;
	while (lst != NULL)
	{
		cone = (t_cone *)lst->value;
		if (cone->bonus.textured && cone->bonus.text.ptr)
			mlx_destroy_image(mlx->mlx_ptr, cone->bonus.text.ptr);
		lst = lst->next;
	}
}
