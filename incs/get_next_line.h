/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magneto <magneto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 19:29:48 by magneto           #+#    #+#             */
/*   Updated: 2022/06/02 17:27:13 by magneto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <stddef.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

char	*get_next_line(int fd);

int		count_char(char *s, int c);

char	*cat_special(char *str1, char *str2);

int		ft_strlen_special(char *s);

char	*end(char *str, int ret);

int		ft_strlen(char *s);

void	increase_array(char *tab);

#endif