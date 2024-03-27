/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_key.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avialle- <avialle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 10:35:35 by avialle-          #+#    #+#             */
/*   Updated: 2024/03/27 11:39:03 by avialle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

int	close_win(t_matrix **matrix)
{
	mlx_destroy_image(DATA.mlx, DATA.imgs.img);
	mlx_destroy_window(DATA.mlx, DATA.win);
	mlx_destroy_display(DATA.mlx);
	free(DATA.mlx);
	free_matrix(matrix, DATA.height);
	exit (EXIT_SUCCESS);
	return (0);
}

int	is_key(int key)
{
	return (key == W || key == S || key == A
		|| key == D || key == UP || key == DOWN || key == LEFT
		|| key == RIGHT || key == PLUS || key == MINUS
		|| key == STAR || key == DIV || key == SPACE
		|| key == UP_Z || key == DOWN_Z || key == G || key == C);
}

void	new_image(t_matrix **matrix)
{
	DATA.imgs.img = mlx_new_image(DATA.mlx, WIDTH, HEIGHT);
	DATA.imgs.addr = mlx_get_data_addr(DATA.imgs.img,
			&DATA.imgs.bits_per_pixel, &DATA.imgs.line_len, &DATA.imgs.endian);
}

int	key_handler(int key, t_matrix **matrix)
{
	printf("key = %d\n", key);
	if (is_key(key))
	{
		do_key(key, matrix);
		mlx_destroy_image(DATA.mlx, DATA.imgs.img);
		new_image(matrix);
	}
	if (key == ESC)
		close_win(matrix);
	return (0);
}
