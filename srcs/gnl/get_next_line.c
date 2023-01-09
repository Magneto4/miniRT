/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magneto <magneto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 19:29:39 by magneto           #+#    #+#             */
/*   Updated: 2022/06/10 18:28:12 by magneto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	fill_buffer(char buf[], int fd, int n)
{
	int	ret;

	if (n == 1 || !(*buf))
	{
		ret = read(fd, buf, BUFFER_SIZE);
		if (ret < 0)
			return (-1);
		buf[ret] = '\0';
		return (ret);
	}
	else
		return (ft_strlen(buf));
}

char	*get_next_line(int fd)
{
	char		*str;
	int			ret;
	static char	buf[FOPEN_MAX][BUFFER_SIZE + 1];

	if (fd >= FOPEN_MAX || fd < 0)
		return (NULL);
	str = malloc(1);
	if (!(str))
		return (NULL);
	str[0] = '\0';
	ret = fill_buffer(buf[fd], fd, 0);
	while (ret > 0)
	{
		if (*(buf[fd]))
			str = cat_special(str, buf[fd]);
		if (!str)
			break ;
		while (*(buf[fd]) && *(buf[fd]) != '\n')
			increase_array(buf[fd]);
		if (*(buf[fd]) && *(buf[fd]) == '\n')
			break ;
		ret = fill_buffer(buf[fd], fd, 1);
	}
	increase_array(buf[fd]);
	return (end(str, ret));
}
