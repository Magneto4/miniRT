/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseniak <nseniak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 13:39:52 by ngiroux           #+#    #+#             */
/*   Updated: 2022/12/21 18:56:08 by nseniak          ###   ########.fr       */
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

#endif /* MINIRT_H */
