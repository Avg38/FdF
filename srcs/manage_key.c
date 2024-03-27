/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_key.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avialle- <avialle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 10:35:35 by avialle-          #+#    #+#             */
/*   Updated: 2024/03/27 11:25:04 by avialle-         ###   ########.fr       */
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

void	center_map(t_matrix **matrix)
{
	if (DATA.is_isometric == 1)
	{
		DATA.offset_x = (WIDTH - DATA.width * DATA.scale) / 2;
		DATA.offset_y = (HEIGHT - DATA.height * DATA.scale) / 2;
	}
	else
	{
		DATA.offset_x = (WIDTH - DATA.width * DATA.scale) / 2;
		DATA.offset_y = (HEIGHT - DATA.height * DATA.scale) / 2;
	}
}

void	rot_key(int key, t_matrix **matrix)
{
	if (key == W)
		DATA.rot_x += 0.08;
	if (key == S)
		DATA.rot_x -= 0.08;
	if (key == A)
		DATA.rot_y += 0.08;
	if (key == D)
		DATA.rot_y -= 0.08;
}

void	offset_key(int key, t_matrix **matrix)
{
	if (key == UP)
		DATA.offset_y -= 10;
	if (key == DOWN)
		DATA.offset_y += 10;
	if (key == LEFT)
		DATA.offset_x -= 10;
	if (key == RIGHT)
		DATA.offset_x += 10;
}

void	scale_key(int key, t_matrix **matrix)
{
	if (key == PLUS && DATA.scale < SCALE_FACTOR * 1000)
		DATA.scale += 0.5 * DATA.scale;
	if (key == MINUS && DATA.scale >= SCALE_FACTOR)
		DATA.scale -= 0.5 * abs((int)DATA.scale) / 2;
}

void	depth_key(int key, t_matrix **matrix)
{
	if (key == UP_Z)
		DATA.depth += 0.1;
	if (key == DOWN_Z)
		DATA.depth -= 0.1;
}

void	gradient_key(int key, t_matrix **matrix)
{
	if (key == G)
	{
		if (DATA.imgs.is_gradient == 1)
			DATA.imgs.is_gradient = 0;
		else
			DATA.imgs.is_gradient = 1;
	}
}

void	do_key(int key, t_matrix **matrix)
{
	
	if (key == C)
		center_map(matrix);
	
	if (key == SPACE)
	{
		if (DATA.is_isometric == 0)
		{
			DATA.is_isometric = 1;
			center_map(matrix);
			DATA.rot_x = -0.52;
			DATA.rot_y = -0.52;
			DATA.rot_z = -0;
			DATA.depth = 0.1;
		}
		else
		{
			DATA.is_isometric = 0;
			center_map(matrix);
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
