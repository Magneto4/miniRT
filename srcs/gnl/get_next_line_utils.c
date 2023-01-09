/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magneto <magneto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 19:29:46 by magneto           #+#    #+#             */
/*   Updated: 2022/06/02 18:19:42 by magneto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen_special(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		i ++;
		if (s[i - 1] == '\n')
			break ;
	}
	return (i);
}

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i ++;
	return (i);
}

char	*cat_special(char *str1, char *str2)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	str = malloc (ft_strlen_special(str1) + ft_strlen_special(str2) + 1);
	if (!str)
		return (end(str, 1));
	while (str1[i])
	{
		str[i] = str1[i];
		i ++;
	}
	while (str2[j])
	{
		str[i + j] = str2[j];
		j ++;
		if (str2[j - 1] == '\n')
			break ;
	}
	str[i + j] = '\0';
	free (str1);
	return (str);
}

void	increase_array(char tab[])
{
	int	i;

	i = 0;
	while (tab[i + 1])
	{
		tab[i] = tab[i + 1];
		i ++;
	}
	tab[i] = '\0';
}

char	*end(char *str, int ret)
{
	if (ret == -1 || !(*str))
	{
		free (str);
		return (NULL);
	}
	return (str);
}
