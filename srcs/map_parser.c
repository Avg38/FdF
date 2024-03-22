/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avialle- <avialle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 18:31:00 by avialle-          #+#    #+#             */
/*   Updated: 2024/03/22 15:16:10 by avialle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	get_height(char *file, int *height)
{
	int		fd;
	char	*line;

	*height = 0;
	fd = open(file, O_RDONLY);
	if (fd < 1)
		ft_exit("Error! Bad fd or empty file", NULL, 0);
	line = get_next_line(fd);
	while (line)
	{
		(*height)++;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
}

void	get_width(char *line, int *width)
{
	int				i;

	if (!line)
		return ;
	i = 0;
	(*width) = 0;
	while (line[i])
	{
		if (line[i] && line[i] != '\n'
			&& line[i] != ' ' && (i == 0 || line[i - 1] == ' '))
			(*width)++;
		i++;
	}
	free(line);
}

char	**line_parser(char *line)
{
	char	**split;

	if (!line)
		return (NULL);
	split = ft_split(line, ' ');
	if (!split)
		return (NULL);
	free(line);
	return (split);
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
		ft_printf("matrix[%d][%d].y = %d\n", y, x, matrix[y][x].y);
		ft_printf("matrix[%d][%d].x = %d\n", y, x, matrix[y][x].x);
		ft_printf("matrix[%d][%d].z = %d\n", y, x, matrix[y][x].z);
		ft_printf("matrix[%d][%d].color = %d\n", y, x, matrix[y][x].color);
		ft_printf("matrix[%d][%d].is_valid = %d\n", y, x, matrix[y][x].is_valid);
		free_2d(split, 2);
		x++;
	}
	ft_printf("\n");
	free_2d(line, x);
}

t_matrix	*ft_calloc_fdf(t_matrix *matrix, int width)
{
	matrix = (t_matrix *)malloc((width + 1) * sizeof(t_matrix));
	if (!matrix)
		return (NULL);
	matrix->x = 0;
	matrix->y = 0;
	matrix->z = 0;
	matrix->color = 0;
	matrix->x_proj = 0;
	matrix->y_proj = 0;
	matrix->z_proj = 0;
	matrix->is_valid = 0;
	matrix->is_isometric = 0;
	matrix->height = 0;
	matrix->width = 0;
	matrix->scale = 0;
	matrix->angle = 0;
	matrix->depth = 0;
	matrix->offset_x = 0;
	matrix->offset_y = 0;
	matrix->mlx = NULL;
	matrix->win = NULL;
	matrix->img = NULL;
	return (matrix);
}

void	set_size_matrix(char *file, int *height, int *width)
{
	// int			y;
	// t_matrix	**matrix;
	int			fd;

	fd = open(file, O_RDONLY);
	if (fd < 1)
		return (ft_exit("Error bad fd or empty file", NULL, 0));
	get_width(get_next_line(fd), width);
	close(fd);
	get_height(file, height);
	if (*width <= 0 || *height <= 0)
		return (ft_exit("get_width or get_height doesn't work", NULL, 0));
	// matrix = (t_matrix **)malloc(*height * sizeof(t_matrix *));
	// if (!matrix)
	// 	return (NULL);
	// y = -1;
	// while (++y < *height)
	// {
	// 	matrix[y] = ft_calloc_fdf(matrix[y], *width);
	// 	if (!matrix[y])
	// 		return (free_matrix(matrix, y),
	// 			ft_exit("get_width or get_height doesn't work", NULL, 0), NULL);
	// }
	// return (matrix);
}

t_matrix	**alloc_matrix(int height, int width)
{
	t_matrix	**matrix;
	int			y;

	matrix = (t_matrix **)malloc(height * sizeof(t_matrix *));
	if (!matrix)
		return (NULL);
	y = -1;
	while (++y < height)
	{
		matrix[y] = ft_calloc_fdf(matrix[y], width);
		if (!matrix[y])
			return (free_matrix(matrix, y),
				ft_exit("get_width or get_height doesn't work", NULL, 0), NULL);
	}
	return (matrix);
}
