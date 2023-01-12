/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngiroux <ngiroux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 16:49:02 by ngiroux           #+#    #+#             */
/*   Updated: 2023/01/11 19:27:57 by ngiroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	ft_check_charset(char c, char *sep)
{
	int	i;

	i = 0;
	while (sep[i])
	{
		if (sep[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	ft_wordlen(char *str, char *sep)
{
	int	i;

	i = 0;
	while (str[i] && ft_check_charset(str[i], sep) == 0)
		i++;
	return (i);
}

int	wordcount_set(char *str, char *sep)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (ft_check_charset(str[i], sep) == 1)
			i++;
		else
		{
			while (str[i] && ft_check_charset(str[i], sep) == 0)
				i++;
			count++;
		}
	}
	return (count);
}

char	*ft_wordcpy(char *str, char *sep, int n)
{
	int		i;
	char	*cpy;

	i = 0;
	cpy = malloc(sizeof(char) * (ft_wordlen(str, sep) + 1));
	if (!cpy)
		return (NULL);
	while (str[i] && i < n)
	{
		cpy[i] = str[i];
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}

char	**split_set(char *str, char *charset)
{
	char	**res;
	int		i;
	int		j;

	if (!str)
		return (NULL);
	res = malloc(sizeof(char *) * (wordcount_set(str, charset) + 1));
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (ft_check_charset(str[i], charset) == 1)
			i++;
		else
		{
			res[j] = ft_wordcpy(str + i, charset, ft_wordlen(str + i, charset));
			j++;
			i += ft_wordlen(str + i, charset);
		}
	}
	res[j] = 0;
	return (res);
}
