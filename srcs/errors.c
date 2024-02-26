/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avialle- <avialle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 17:09:24 by avialle-          #+#    #+#             */
/*   Updated: 2024/02/26 12:37:41 by avialle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	ft_exit(char *msg, t_map **matrix, int height)
{
	if (matrix)
		free_matrix(matrix, height);
	ft_printf("%s\n", msg);
	exit(EXIT_FAILURE);
}

void	free_2d(char **str, int len)
{
	int	i;

	i = 0;
	if (str)
	{
		while (i < len)
		{
			free(str[i]);
			i++;
		}
		free(str);
	}
}

void	free_matrix(t_map **matrix, int height)
{
	int	y;

	y = 0;
	if (!matrix)
		return ;
	while (y < height)
	{
		free(matrix[y]);
		y++;
	}
	free(matrix);
}

void	height_width(char *file)
{
	int	height;
	int	width;
	int	tmp;
	int	i;
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 1)
		ft_exit("Error bad fd or empy file", NULL, 0);
	height = get_height(file);
	if (height < 1)
		return (close(fd), ft_exit("Error colunm size < 1", NULL, 0));
	i = 1;
	tmp = get_width(get_next_line(fd));
	if (tmp == 0)
		return (close(fd), ft_exit("Error line size < 1", NULL, 0));
	while (i < height)
	{
		width = get_width(get_next_line(fd));
		if (!width || width != tmp)
			return (close(fd), ft_exit("Error line size", NULL, 0));
		i++;
	}
	close(fd);
}
