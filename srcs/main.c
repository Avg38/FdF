/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avialle- <avialle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 16:30:44 by avialle-          #+#    #+#             */
/*   Updated: 2024/02/26 14:20:39 by avialle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

// void	set_data(t_map **matrix)
// {
// 	DATA.mlx_ptr = mlx_init();
// 	DATA.win_ptr = mlx_new_window(DATA.mlx_ptr, 800, 600, "Example");

// }

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
	if (fd < 1)
		ft_exit("Error! Bad fd or file empty", matrix, height);
	y = -1;
	while (++y < height)
		fill_matrix(line_parser(get_next_line(fd)), matrix, width, &y);
	// set_data(matrix);
	// mlx_loop(DATA.mlx_ptr);
	close(fd);
	// display_matrix(matrix, height, width);
	free_matrix(matrix, height);
}



int	main(int ac, char **av)
{
	is_error(ac, av[1]);
	fdf(av[1]);
	return (0);
}
