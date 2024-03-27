/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   size_matrix.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avialle- <avialle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 15:54:44 by avialle-          #+#    #+#             */
/*   Updated: 2024/03/27 16:06:43 by avialle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"

void	get_height(char *file, int *height)
{
	int		fd;
	char	*line;

	*height = 0;
	fd = open(file, O_RDONLY);
	if (fd < 1)
		ft_exit("Error! Bad fd or empty file", NULL, 0);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		(*height)++;
		free(line);
	}
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

void	size_matrix(char *file, int *height, int *width)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 1)
		return (ft_exit("Error bad fd or empty file", NULL, 0));
	get_width(get_next_line(fd), width);
	close(fd);
	get_height(file, height);
	if (*width <= 0 || *height <= 0)
		return (ft_exit("get_width or get_height doesn't work", NULL, 0));
}
