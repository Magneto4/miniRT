/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngiroux <ngiroux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 13:53:27 by ngiroux           #+#    #+#             */
/*   Updated: 2022/12/20 17:19:10 by ngiroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	put_error(char *str)
{
	write(2, "Error: ", 7);
	write(2, str, __strlen(str));
	write(2, "\n", 1);
	return (EXIT_FAILURE);
}

void	put_error_null(char *str)
{
	write(2, "Error: ", 7);
	write(2, str, __strlen(str));
	write(2, "\n", 1);
}

bool	put_error_false(char *str)
{
	write(2, "Error: ", 7);
	write(2, str, __strlen(str));
	write(2, "\n", 1);
	return (false);
}
