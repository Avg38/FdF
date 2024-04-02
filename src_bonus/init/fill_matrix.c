/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_matrix.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avialle- <avialle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 14:17:28 by avialle-          #+#    #+#             */
/*   Updated: 2024/04/02 15:34:20 by avialle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf_bonus.h"

void	fill_color(t_matrix **matrix)
{
	int	y;
	int	x;

	y = 0;
	while (y < matrix[0][0].height)
	{
		x = 0;
		while (matrix[y][x].is_valid)
		{
			if (matrix[y][x].z > 0)
				matrix[y][x].color = 0x90F8E4;
			else if (matrix[y][x].z < 0)
				matrix[y][x].color = 0x90CAF8;
			x++;
		}
		y++;
	}
}

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
	int		no_color;

	x = 0;
	no_color = 1;
	while (x < matrix[0][0].width)
	{
		matrix[y][x].y = y;
		matrix[y][x].x = x;
		matrix[y][x].z = ft_atoi(line[x]);
		if (matrix[y][x].z < -10000 || matrix[y][x].z > 10000)
			ft_exit("Values are too high", matrix, matrix[0][0].height);
		matrix[y][x].color = ft_atoi_base(get_color(line[x]),
				"0123456789abcdef");
		if (matrix[y][x].color != -1 && matrix[y][x].color != 0xFFFFFF)
			no_color = 0;
		matrix[y][x].is_valid = 1;
		x++;
	}
	if (no_color == 1)
		fill_color(matrix);
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
