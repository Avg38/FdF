/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_key.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avialle- <avialle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 10:35:35 by avialle-          #+#    #+#             */
/*   Updated: 2024/03/26 16:08:33 by avialle-         ###   ########.fr       */
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
		|| key == UP_Z || key == DOWN_Z);
}

void	do_key(int key, t_matrix **matrix)
{
	if (key == UP)
		DATA.offset_y -= 10;
	if (key == DOWN)
		DATA.offset_y += 10;
	if (key == LEFT)
		DATA.offset_x -= 10;
	if (key == RIGHT)
		DATA.offset_x += 10;
	if (key == W)
		DATA.rot_x += 0.08;
	if (key == S)
		DATA.rot_x -= 0.08;
	if (key == A)
		DATA.rot_y += 0.08;
	if (key == D)
		DATA.rot_y  -= 0.08;
	if (key == PLUS && DATA.scale < SCALE_FACTOR * 1000)
		DATA.scale += 1 * DATA.scale;
	if (key == MINUS && DATA.scale >= SCALE_FACTOR)
		DATA.scale -= 1 * abs((int)DATA.scale) / 2;
	if (key == STAR)
		DATA.angle += 0.05;
	if (key == DIV)
		DATA.angle -= 0.05;
	if (key == UP_Z)
		DATA.depth += 0.1;
	if (key == DOWN_Z)
		DATA.depth -= 0.1;
	if (key == SPACE)
	{
		if (DATA.is_isometric == 0)
		{
			DATA.is_isometric = 1;
			DATA.offset_x = (WIDTH - DATA.width * DATA.scale * DATA.angle * 0.1) / 2;
			DATA.offset_y = (HEIGHT - DATA.height * DATA.scale * DATA.angle) / 2;
		}
		else
		{
			DATA.is_isometric = 0;
			DATA.offset_x = (WIDTH - DATA.width * DATA.scale) / 2;
			DATA.offset_y = (HEIGHT - DATA.height * DATA.scale) / 2;
		}
	}
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
