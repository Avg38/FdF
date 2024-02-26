/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avialle- <avialle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 16:30:44 by avialle-          #+#    #+#             */
/*   Updated: 2024/02/26 11:40:17 by avialle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	fdf(char *file)
{
	t_map	**matrix;
	int		width;
	int		height;
	int		fd;
	int		y;

	width = 0;
	height = 0;
	matrix = set_size_matrix(file, &width, &height);
	ft_printf("height = %d, width = %d\n", height, width);
	if (!matrix)
		ft_exit("Error malloc matrix", NULL, 0);
	fd = open(file, O_RDONLY);
	if (fd <= 0)
		ft_exit("Error! Bad fd or file empty", matrix, height);
	y = 0;
	while (y < height)
		fill_matrix(line_parser(get_next_line(fd)), matrix, width, &y);
	close(fd);
	// display_matrix(matrix, height, width);
	free_matrix(matrix, height);
}

int	main(int ac, char **av)
{
	int	fd;

	if (ac == 2)
	{
		if (!ft_strnstr(av[1], ".fdf", 4))
			ft_exit("Error! \".fdf\" is needed", NULL, 0);
		fd = open(av[1], O_RDONLY);
		if (fd <= 0)
			ft_exit("Error! Bad fd or file empty", NULL, 0);
		close(fd);
		height_width(av[1]);
		fdf(av[1]);
	}
	else
		ft_exit("Notice : ./fdf <maps.fdf>", NULL, 0);
	return (0);
}
