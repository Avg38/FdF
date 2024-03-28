/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_key.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avialle- <avialle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 10:35:35 by avialle-          #+#    #+#             */
/*   Updated: 2024/03/28 11:27:04 by avialle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf_bonus.h"

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

int	is_key(int key)
{
	return (key == W || key == S || key == A
		|| key == D || key == UP || key == DOWN || key == LEFT
		|| key == RIGHT || key == PLUS || key == MINUS
		|| key == STAR || key == DIV || key == SPACE
		|| key == UP_Z || key == DOWN_Z || key == G || key == C
		|| key == V);
}

void	new_image(t_matrix **matrix)
{
	matrix[0][0].imgs.img = mlx_new_image(matrix[0][0].mlx, WIDTH, HEIGHT);
	matrix[0][0].imgs.addr = mlx_get_data_addr(matrix[0][0].imgs.img,
			&matrix[0][0].imgs.bits_per_pixel, &matrix[0][0].imgs.line_len, &matrix[0][0].imgs.endian);
}

int	key_handler(int key, t_matrix **matrix)
{
	printf("key = %d\n", key);
	if (is_key(key))
	{
		do_key(key, matrix);
		mlx_destroy_image(matrix[0][0].mlx, matrix[0][0].imgs.img);
		new_image(matrix);
	}
	if (key == ESC)
		close_win(matrix);
	return (0);
}
