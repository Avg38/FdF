/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_matrix.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avialle- <avialle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 14:17:28 by avialle-          #+#    #+#             */
/*   Updated: 2024/03/27 16:20:20 by avialle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf_bonus.h"

void	fill_color(t_matrix **matrix)
{
	int	y;
	int	x;

	y = 0;
	while (y < DATA.height)
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

void	fill_data(char **line, t_matrix **matrix, int y)
{
	char	**split;
	int		x;
	int		no_color;

	x = 0;
	no_color = 1;
	while (x < DATA.width)
	{
		matrix[y][x].y = y;
		matrix[y][x].x = x;
		split = ft_split_color(line[x]);
		if (!split || !split[0])
			return (free_2d(line, x));
		matrix[y][x].z = ft_atoi(split[0]);
		matrix[y][x].color = ft_atoi_base(split[1], "0123456789abcdef");
		if (matrix[y][x].color != -1 && matrix[y][x].color != 0xFFFFFF)
			no_color = 0;
		matrix[y][x].is_valid = 1;
		free_2d(split, 2);
		x++;
	}
	if (no_color == 1)
		fill_color(matrix);
	free_2d(line, x);
}

void	fill_zero(t_matrix *matrix)
{
	matrix->x = 0;
	matrix->y = 0;
	matrix->z = 0;
	matrix->color = 0;
	matrix->x_proj = 0;
	matrix->y_proj = 0;
	matrix->z_proj = 0;
	matrix->is_valid = 0;
	matrix->height = 0;
	matrix->width = 0;
	matrix->scale = 0;
	matrix->depth = 0;
	matrix->offset_x = 0;
	matrix->offset_y = 0;
	matrix->rot_x = 0;
	matrix->rot_y = 0;
	matrix->rot_z = 0;
	matrix->mlx = NULL;
	matrix->win = NULL;
}

void	fill_matrix(char *file, t_matrix **matrix)
{
	int	fd;
	int	y;

	fd = open(file, O_RDONLY);
	if (fd < 1)
		ft_exit("Error! Bad fd or file empty", matrix, DATA.height);
	y = -1;
	// ft_printf("%d\n", DATA.height);
	while (++y < DATA.height)
		fill_data(line_parser(get_next_line(fd)), matrix, y);
	close(fd);
}
