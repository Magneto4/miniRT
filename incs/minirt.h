/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseniak <nseniak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 13:39:52 by ngiroux           #+#    #+#             */
/*   Updated: 2022/12/21 19:11:08 by nseniak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

// 🎩 Includes
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <fcntl.h>

# include "scene.h"
# include "types.h"
# include "elem.h"
# include "../mlx/mlx.h"

// 🕵️‍♂️ Define
# define HEIGHT 500
# define WIDTH 500

// 🏳️ Parse
t_scene	*__parse(char *file);

// 🏔️ MiniRT

// 🧰 Utils
int		put_error(char *str);
void	put_error_null(char *str);
bool	put_error_false(char *str);

// 📚 Libs
int		__strlen(char *str);
int		__strcmp(const char *s1, const char *s2);

//window
int		init_window(t_minirt *minirt);
void	start_loop(t_minirt *minirt);
int		close_hook(void *void_minirt);
int		key(int keycode, void *void_minirt);

#endif /* MINIRT_H */
