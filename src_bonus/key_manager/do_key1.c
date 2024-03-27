/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_key1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avialle- <avialle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 11:39:14 by avialle-          #+#    #+#             */
/*   Updated: 2024/03/27 15:49:08 by avialle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf_bonus.h"

void	center_key(t_matrix **matrix)
{
	if (DATA.isometric == 1)
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

void	isometric_key(t_matrix **matrix)
{
	DATA.isometric *= -1;
	if (DATA.isometric == 1)
	{
		center_key(matrix);
		DATA.rot_x = -0.52;
		DATA.rot_y = -0.52;
		DATA.rot_z = -0;
		DATA.depth = 1;
	}
	else
		center_key(matrix);
}

void	diagonal_key(t_matrix **matrix)
{
	DATA.imgs.diagonal *= -1;
}

void	do_key(int key, t_matrix **matrix)
{
	if (key == W || key == S || key == A || key == D)
		rot_key(key, matrix);
	if (key == UP || key == DOWN || key == LEFT || key == RIGHT)
		offset_key(key, matrix);
	if (key == PLUS || key == MINUS)
		scale_key(key, matrix);
	if (key == UP_Z || key == DOWN_Z)
		depth_key(key, matrix);
	if (key == C)
		center_key(matrix);
	if (key == G)
		gradient_key(matrix);
	if (key == V)
		diagonal_key(matrix);
	if (key == SPACE)
		isometric_key(matrix);
}
