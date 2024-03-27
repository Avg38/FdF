/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avialle- <avialle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 16:30:44 by avialle-          #+#    #+#             */
/*   Updated: 2024/03/27 16:32:18 by avialle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

int	close_win(int key, t_matrix **matrix)
{
	if (key == 17)
	{
		mlx_destroy_image(DATA.mlx, DATA.imgs.img);
		mlx_destroy_window(DATA.mlx, DATA.win);
		mlx_destroy_display(DATA.mlx);
		free(DATA.mlx);
		free_matrix(matrix, DATA.height);
		exit (EXIT_SUCCESS);
	}
	return (0);
}

t_matrix	**init_fdf(char *file, t_matrix **matrix)
{
	int	width;
	int	height;

	height = 0;
	width = 0;
	size_matrix(file, &height, &width);
	matrix = alloc_matrix(height, width);
	init_data(matrix, height, width);
	fill_matrix(file, matrix);
	// display_matrix(matrix);
	init_proj(matrix);
	return (matrix);
}

int	main(int ac, char **av)
{
	t_matrix	**matrix;

	matrix = NULL;
	check_args(ac, av[1]);
	matrix = init_fdf(av[1], matrix);
	mlx_key_hook(DATA.win, close_win, matrix);
	mlx_hook(DATA.win, 2, 1L << 0, close_win, matrix);
	frame(matrix);
	mlx_loop(DATA.mlx);
	return (0);
}
