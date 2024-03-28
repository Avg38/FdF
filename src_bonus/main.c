/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avialle- <avialle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 16:30:44 by avialle-          #+#    #+#             */
/*   Updated: 2024/03/28 14:11:36 by avialle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf_bonus.h"

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
	mlx_hook(matrix[0][0].win, 2, 1L << 0, &key_handler, matrix);
	mlx_hook(matrix[0][0].win, 17, (1L<<17), &close_win, matrix);
	mlx_loop_hook(matrix[0][0].mlx, frame, matrix);
	mlx_loop(matrix[0][0].mlx);
	return (0);
}
