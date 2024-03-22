/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_and_fill.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avialle- <avialle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 15:56:19 by avialle-          #+#    #+#             */
/*   Updated: 2024/03/22 16:08:10 by avialle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	set_DATA(t_matrix **matrix, int height, int width)
{
	DATA.height = height;
	DATA.width = width;
	DATA.mlx = mlx_init();
	DATA.win = mlx_new_window(DATA.mlx, 800, 600, "Example");
	DATA.img = mlx_new_image(DATA.mlx, DATA.width, DATA.height);
}


void	fill_data(char **line, t_matrix **matrix, int y)
{
	char	**split;
	int		x;

	x = 0;
	while (x < DATA.width)
	{
		matrix[y][x].y = y;
		matrix[y][x].x = x;
		split = ft_split_color(line[x]);
		if (!split || !split[0])
			return (free_2d(line, x));
		matrix[y][x].z = ft_atoi(split[0]);
		matrix[y][x].color = ft_atoi_base(split[1], "0123456789abcdef");
		matrix[y][x].is_valid = 1;
		free_2d(split, 2);
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
		ft_exit("Error! Bad fd or file empty", matrix, DATA.height);
	y = -1;
	ft_printf("DATA.height = %d\n", DATA.height);
	while (++y < DATA.height)
		fill_data(line_parser(get_next_line(fd)), matrix, y);
	close(fd);
}

void	fill_zero(t_matrix *matrix, int width)
{
	int	i;

	i = -1;
	while (++i <= width)
	{
		matrix[i].x = 0;
		matrix[i].y = 0;
		matrix[i].z = 0;
		matrix[i].color = 0;
		matrix[i].x_proj = 0;
		matrix[i].y_proj = 0;
		matrix[i].z_proj = 0;
		matrix[i].is_valid = 0;
		matrix[i].is_isometric = 0;
		matrix[i].height = 0;
		matrix[i].width = 0;
		matrix[i].scale = 0;
		matrix[i].angle = 0;
		matrix[i].depth = 0;
		matrix[i].offset_x = 0;
		matrix[i].offset_y = 0;
		matrix[i].mlx = NULL;
		matrix[i].win = NULL;
		matrix[i].img = NULL;
	}
}

t_matrix	**alloc_matrix(int height, int width)
{
	t_matrix	**matrix;
	int			y;

	matrix = (t_matrix **)malloc(height * sizeof(t_matrix *));
	if (!matrix)
		return (ft_exit("malloc matrix failed", NULL, 0), NULL);
	y = -1;
	while (++y < height)
	{
		matrix[y] = (t_matrix *)malloc((width + 1) * sizeof(t_matrix));
		if (!matrix)
			return (ft_exit("malloc matrix element failed", matrix, y), NULL);
		fill_zero(matrix[y], width);
		if (!matrix[y])
			return (free_matrix(matrix, y),
				ft_exit("get_width or get_height doesn't work", NULL, 0), NULL);
	}
	return (matrix);
}