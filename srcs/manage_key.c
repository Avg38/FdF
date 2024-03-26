/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_key.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avialle- <avialle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 10:35:35 by avialle-          #+#    #+#             */
/*   Updated: 2024/03/26 11:12:43 by avialle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

int	close_win(t_matrix **matrix)
{
	mlx_destroy_window(DATA.mlx, DATA.win);
	mlx_destroy_display(DATA.mlx);
	free(DATA.mlx);
	free_matrix(matrix, DATA.height);
	exit (EXIT_SUCCESS);
	return (0);
}

int	is_key(int key)
{
	return (key == UP || key == DOWN || key == LEFT
		|| key == RIGHT || key == SPACE
		|| key == MINUS || key == PLUS || key == STAR
		|| key == DIV || key == UP_Z || key == DOWN_Z);
}

void	do_key(int key, t_matrix **matrix)
{
	if (key == PLUS)
		DATA.scale += 1;
	if (key == MINUS)
		DATA.scale -= 1;
	if (key == STAR)
		DATA.angle += 0.05;
	if (key == DIV)
		DATA.angle -= 0.05;
	if (key == LEFT)
		DATA.offset_x -= 5;
	if (key == RIGHT)
		DATA.offset_x += 5;
	if (key == UP)
		DATA.offset_y -= 5;
	if (key == DOWN)
		DATA.offset_y += 5;
}

void	new_image(t_matrix **matrix)
{
	DATA.imgs.img = mlx_new_image(DATA.mlx, WIDTH, HEIGHT);
	DATA.imgs.addr = mlx_get_data_addr(DATA.imgs.img, &DATA.imgs.bits_per_pixel, &DATA.imgs.line_len, &DATA.imgs.endian);
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
