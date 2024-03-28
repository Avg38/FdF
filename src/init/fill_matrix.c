/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_matrix.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avialle- <avialle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 14:17:28 by avialle-          #+#    #+#             */
/*   Updated: 2024/03/28 14:36:21 by avialle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"

char	*get_color(char *str)
{
	if (!str)
		return (NULL);
	while (*str != 'x' && *str)
	{
		str++;
	}
	if (*str == 'x')
		return (++str);
	return (NULL);
}

void	fill_data(char **line, t_matrix **matrix, int y)
{
	int		x;

	x = 0;
	while (x < matrix[0][0].width)
	{
		matrix[y][x].y = y;
		matrix[y][x].x = x;
		matrix[y][x].z = ft_atoi(line[x]);
		matrix[y][x].color = ft_atoi_base(get_color(line[x]), "0123456789abcdef");
		matrix[y][x].is_valid = 1;
		x++;
	}
	free_2d(line, x);
}

void	fill_matrix(char *file, t_matrix **matrix)
{
	int	fd;
	int	y;

	fd = open(file, O_RDONLY);
	if (fd < 1)
		ft_exit("Error! Bad fd or file empty", matrix, matrix[0][0].height);
	y = -1;
	while (++y < matrix[0][0].height)
		fill_data(line_parser(get_next_line(fd)), matrix, y);
	close(fd);
}
