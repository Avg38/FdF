/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avialle- <avialle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 17:09:24 by avialle-          #+#    #+#             */
/*   Updated: 2024/03/23 11:05:08 by avialle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	ft_exit(char *msg, t_matrix **matrix, int height)
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

void	free_matrix(t_matrix **matrix, int height)
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
	get_height(file, &height);
	if (height < 1)
		return (close(fd), ft_exit("Error colunm size < 1", NULL, 0));
	get_width(get_next_line(fd), &width);
	if (width == 0)
		return (close(fd), ft_exit("Error! Line size < 1", NULL, 0));
	i = 1;
	while (i < height)
	{
		get_width(get_next_line(fd), &tmp);
		if (!tmp || tmp != width)
			return (close(fd), ft_exit("Error! Line size", NULL, 0));
		i++;
	}
	close(fd);
}
