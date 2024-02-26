/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avialle- <avialle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 18:31:00 by avialle-          #+#    #+#             */
/*   Updated: 2024/02/26 12:37:11 by avialle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

int	get_height(char *file)
{
	int		fd;
	int		i;
	char	*line;

	if (!file)
		return (-1);
	i = 0;
	fd = open(file, O_RDONLY);
	if (fd <= 0)
		return (-1);
	line = get_next_line(fd);
	while (line)
	{
		i++;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	return (i);
}

int	get_width(char *line)
{
	int				i;
	unsigned int	count;

	if (!line)
		return (-1);
	i = 0;
	count = 0;
	while (line[i])
	{
		if (line[i] && line[i] != '\n'
			&& line[i] != ' ' && (i == 0 || line[i - 1] == ' '))
			count++;
		i++;
	}
	free(line);
	return (count);
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

void	fill_matrix(char **line, t_map **matrix, int width, int *y)
{
	char	**split;
	int		x;

	x = 0;
	while (x < width)
	{
		matrix[*y][x].y = *y;
		matrix[*y][x].x = x;
		split = ft_split_color(line[x]);
		if (!split || !split[0])
			return (free_2d(line, x));
		matrix[*y][x].z = ft_atoi(split[0]);
		matrix[*y][x].color = ft_atoi_base(split[1], "0123456789abcdef");
		free_2d(split, 2);
		x++;
	}
	(*y)++;
	free_2d(line, x);
}

t_map	**set_size_matrix(char *file, int *width, int *height)
{
	int		y;
	t_map	**matrix;
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd < 1)
		return (ft_exit("Error bad fd or empty file", NULL, 0), NULL);
	*width = get_width(get_next_line(fd));
	close(fd);
	*height = get_height(file);
	if (*width <= 0 || *height <= 0)
		return (ft_exit("get_width or get_height doesn't work", NULL, 0), NULL);
	matrix = (t_map **)malloc(*height * sizeof(t_map *));
	if (!matrix)
		return (NULL);
	y = 0;
	while (y < *height)
	{
		matrix[y] = (t_map *)malloc(*width * sizeof(t_map));
		if (!matrix[y])
			return (free_matrix(matrix, y),
				ft_exit("get_width or get_height doesn't work", NULL, 0), NULL);
		y++;
	}
	return (matrix);
}
