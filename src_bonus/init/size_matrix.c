/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   size_matrix.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avialle- <avialle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 15:54:44 by avialle-          #+#    #+#             */
/*   Updated: 2024/04/02 12:33:50 by avialle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf_bonus.h"

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

int	get_width(char *line)
{
	int	i;
	int	width;

	if (!line)
		return (0);
	i = 0;
	width = 0;
	while (line[i])
	{
		if (line[i] && line[i] != '\n'
			&& line[i] != ' ' && (i == 0 || line[i - 1] == ' '))
			width++;
		i++;
	}
	return (width);
}

void	get_size(char *file, int *height, int *width)
{
	int		fd;
	char	*line;

	*height = 0;
	fd = open(file, O_RDONLY);
	if (fd < 1)
		ft_exit("Error! Bad fd or empty file", NULL, 0);
	line = get_next_line(fd);
	*width = get_width(line);
	if (!*width)
		ft_exit("Error! line width", NULL, 0);
	while (line)
	{
		(*height)++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}

int	get_height(char *file, int *width)
{
	int		fd;
	char	*line;
	int		height;

	height = 0;
	fd = open(file, O_RDONLY);
	if (fd < 1)
		ft_exit("Error! Bad fd or empty file", NULL, 0);
	line = get_next_line(fd);
	*width = get_width(line);
	if (!*width)
		ft_exit("Error! line width", NULL, 0);
	while (line)
	{
		height++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (height);
}

// void	size_matrix(char *file, int *height, int *width)
// {
// 	get_size(file, height, width);
// 	if (*width <= 0 || *height <= 0)
// 		return (ft_exit("get_width or get_height doesn't work", NULL, 0));
// }

t_matrix	**set_size_matrix(char *file, int *height, int *width)
{
	t_matrix	**matrix;
	int			y;

	ft_printf("start get_size\n");
	get_size(file, height, width);
	ft_printf("end get_size\n");
	if (*width <= 0 || *height <= 0)
		ft_exit("get_width or get_height doesn't work", NULL, 0);
	matrix = (t_matrix **)ft_calloc(*height, sizeof(t_matrix *));
	if (!matrix)
		ft_exit("malloc matrix failed", NULL, 0);
	y = -1;
	ft_printf("start callc\n");
	while (++y < *height)
	{
		matrix[y] = (t_matrix *)ft_calloc(*width + 1, sizeof(t_matrix));
		if (!matrix[y])
			ft_exit("malloc matrix element failed", matrix, y);
	}
	ft_printf("end callc\n");
	return (matrix);
}
