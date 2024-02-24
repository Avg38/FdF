/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avialle- <avialle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 16:30:44 by avialle-          #+#    #+#             */
/*   Updated: 2024/02/23 19:18:09 by avialle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

int	fdf(char *file)
{
	t_map	**matrix;
	int		width;
	int		height;
	int		fd;
	int		y;

	matrix = NULL;
	width = 0;
	height = 0;
	if (set_size_matrix(&matrix, file, &width, &height) != 0)
		return (-1);
	ft_printf("height = %d, width = %d\n", height, width);
	if (!matrix)
		return (-1);
	fd = open(file, O_RDONLY);
	if (fd <= 0)
		return (free_matrix(matrix, 0), -1);
	y = 0;
	while (y < height)
		fill_matrix(line_parser(get_next_line(fd)), &matrix, width, &y);
	close(fd);
	display_matrix(matrix, height, width);
	free_matrix(matrix, height);
	return (0);
}

int	main(int ac, char **av)
{
	int	fd;

	if (ac == 2)
	{
		if (!ft_strnstr(av[1], ".fdf", 4))
			ft_exit("Error! \".fdf\" is needed");
		fd = open(av[1], O_RDONLY);
		if (fd <= 0)
			ft_exit("Error! Bad fd or file empty");
		close(fd);
		// if (width_height())
		// 	ft_exit("Error! Lines ");
		if (fdf(av[1]) != 0)
			ft_exit("ERROR");
	}
	else
		ft_exit("Notice : ./fdf <maps.fdf>");
	return (0);
}
