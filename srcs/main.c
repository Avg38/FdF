/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avialle- <avialle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 16:30:44 by avialle-          #+#    #+#             */
/*   Updated: 2024/03/22 15:16:29 by avialle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	set_DATA(t_matrix **matrix, int height, int width)
{
	DATA.height = height;
	DATA.width = width;
	DATA.mlx = mlx_init();
	DATA.win = mlx_new_window(DATA.mlx, 800, 600, "Example");
}

void	fill_matrix(char *file, t_matrix **matrix)
{
	// t_matrix	**matrix;
	// int		width;
	// int		height;
	int		fd;
	int		y;

	// width = 0;
	// height = 0;
	// matrix = set_size_matrix(file, &width, &height);
	// if (!matrix)
	// 	ft_exit("Error malloc matrix", NULL, 0);
	fd = open(file, O_RDONLY);
	if (fd < 1)
		ft_exit("Error! Bad fd or file empty", matrix, DATA.height);
	// ft_printf("DATA.height = %d\n", DATA.height);
	// ft_printf("DATA.width = %d\n", DATA.width);
	y = -1;
	while (++y < DATA.height)
		fill_data(line_parser(get_next_line(fd)), matrix, y);
	// ft_printf("height = %d, width = %d\n", DATA.height, DATA.width);
	close(fd);
}

void	init_fdf(char *file)
{
	t_matrix	**matrix;
	int			width;
	int			height;

	height = 0;
	width = 0;
	set_size_matrix(file, &height, &width);
	matrix = alloc_matrix(height, width);
	set_DATA(matrix, height, width);
	fill_matrix(file, matrix);
	// display_matrix(matrix);
	mlx_loop(DATA.mlx);
	free_matrix(matrix, DATA.height);
}

int	main(int ac, char **av)
{
	check_args(ac, av[1]);
	init_fdf(av[1]);
	// fdf(av[1]);
	return (0);
}
