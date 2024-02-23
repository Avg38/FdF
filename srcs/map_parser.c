/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avialle- <avialle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 18:31:00 by avialle-          #+#    #+#             */
/*   Updated: 2024/02/23 19:14:22 by avialle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

int	get_height(char *file)
{
	int	fd;
	int	i;

	if (!file)
		return (-1);
	i = 0;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (-1);
	while (get_next_line(fd))
		i++;
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
		if (line[i] != ' ' && (line[i - 1] == ' ' || i == 0))
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

void	fill_matrix(char **line, t_map ***matrix, int width, int *y)
{
	char	**split;
	int		x;

	x = 0;
	while (x < width)
	{
		(*matrix)[*y][x].y = *y;
		(*matrix)[*y][x].x = x;
		split = ft_split_color(line[x]);
		if (!split)
			return (free2d(line));
		(*matrix)[*y][x].z = ft_atoi(split[0]);
		(*matrix)[*y][x].color = ft_atoi_base(split[1], "0123456789abcdef");
		free2d(split);
		x++;
	}
	(*y)++;
	free2d(line);
}

void	set_size_matrix(t_map ***matrix, char *file, int *width, int *height)
{
	int	fd;
	int	y;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return ;
	*width = get_width(get_next_line(fd));
	close(fd);
	*height = get_height(file);
	if (*width < 0 || *height < 0)
		return ;
	(*matrix) = (t_map **)malloc(*height * sizeof(t_map *));
	if (!(*matrix))
		return ;
	y = 0;
	while (y < *height)
	{
		(*matrix)[y] = (t_map *)malloc(*width * sizeof(t_map));
		if (!(*matrix)[y])
			return (free_matrix(*matrix));
		y++;
	}
}
