/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngiroux <ngiroux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 14:22:18 by ngiroux           #+#    #+#             */
/*   Updated: 2023/01/08 16:48:53 by ngiroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"


int	__wordcount(char **line)
{
	int	i;

	i = 0;
	while (line[i])
		i++;
	return (i);
}

int	__strlen(char *str)
{
	char	*tmp;

	if (!str || !*str)
		return (0);
	tmp = str;
	while (*tmp)
		tmp++;
	return (tmp - str);
}

int	__strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	if (!*s1 || !*s2)
		return (0);
	while (s1[i] == s2[i] && s1[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
