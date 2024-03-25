/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_key.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avialle- <avialle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 10:35:35 by avialle-          #+#    #+#             */
/*   Updated: 2024/03/25 16:56:11 by avialle-         ###   ########.fr       */
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
		DATA.scale += 3;
	if (key == MINUS)
		DATA.scale -= 3;
	if (key == STAR)
		DATA.angle += 0.05;
	if (key == DIV)
		DATA.angle -= 0.05;
	if (key == LEFT)
		DATA.offset_x -= 3;
	if (key == RIGHT)
		DATA.offset_x += 3;
	if (key == UP)
		DATA.offset_y -= 3;
	if (key == DOWN)
		DATA.offset_y += 3;
}

void	draw_black(t_matrix **matrix)
{
	int	y;
	int	x;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			put_pixel(DATA.imgs, x, y, 0);
			x++;
		}
		y++;
	}
}

int	key_handler(int key, t_matrix **matrix)
{
	printf("key = %d\n", key);
	if (is_key(key))
	{
		draw_black(matrix);
		do_key(key, matrix);
	}
	if (key == ESC)
		close_win(matrix);
	return (0);
}
