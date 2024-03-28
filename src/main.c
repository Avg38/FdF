/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avialle- <avialle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 16:30:44 by avialle-          #+#    #+#             */
/*   Updated: 2024/03/28 14:33:19 by avialle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

int	close_win(t_matrix **matrix)
{
	mlx_destroy_image(matrix[0][0].mlx, matrix[0][0].imgs.img);
	mlx_destroy_window(matrix[0][0].mlx, matrix[0][0].win);
	mlx_destroy_display(matrix[0][0].mlx);
	free(matrix[0][0].mlx);
	free_matrix(matrix, matrix[0][0].height);
	exit (EXIT_SUCCESS);
	return (0);
}

int	esc_handler(int key, t_matrix **matrix)
{
	if (key == 65307)
		close_win(matrix);
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
	init_proj(matrix);
	return (matrix);
}

int	main(int ac, char **av)
{
	t_matrix	**matrix;

	matrix = NULL;
	check_args(ac, av[1]);
	matrix = init_fdf(av[1], matrix);
	mlx_key_hook(matrix[0][0].win, &esc_handler, matrix);
	mlx_hook(matrix[0][0].win, 17, 1L << 17, &close_win, matrix);
	frame(matrix);
	mlx_loop(matrix[0][0].mlx);
	return (0);
}
