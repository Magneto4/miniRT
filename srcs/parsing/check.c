/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngiroux <ngiroux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 12:57:05 by ngiroux           #+#    #+#             */
/*   Updated: 2022/12/20 13:05:54 by ngiroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int __wordcount(char **line)
{
	int i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

bool	__check_vector(char **vec)
{
	if (__wordcount(vec) != 3)
		return (false);
	return (true);
}

bool	__check_type(char **line)
{
	if ((line[0] == "A" && __wordcount(line) != 3) ||
		(line[0] == "c" && __wordcount(line) != 4) ||
		(line[0] == "l" && __wordcount(line) != 4) ||
		(line[0] == "sp" && __wordcount(line) != 4) ||
		(line[0] == "pl" && __wordcount(line) != 4) ||
		(line[0] == "sq" && __wordcount(line) != 5) ||
		(line[0] == "cy" && __wordcount(line) != 6) ||
		(line[0] == "tr" && __wordcount(line) != 5))
		return (false);
	return (true);
}
