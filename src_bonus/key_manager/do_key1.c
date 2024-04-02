/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_key1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avialle- <avialle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 11:39:14 by avialle-          #+#    #+#             */
/*   Updated: 2024/04/02 11:55:43 by avialle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf_bonus.h"

void	center_key(t_matrix **matrix)
{
	if (matrix[0][0].isometric == 1)
	{
		matrix[0][0].offset_x = (WIN_W
				- matrix[0][0].width * matrix[0][0].scale) / 2;
		matrix[0][0].offset_y = (WIN_H
				- matrix[0][0].height * matrix[0][0].scale) / 2;
	}
	else
	{
		matrix[0][0].offset_x = (WIN_W
				- matrix[0][0].width * matrix[0][0].scale) / 2;
		matrix[0][0].offset_y = (WIN_H
				- matrix[0][0].height * matrix[0][0].scale) / 2;
	}
}

void	isometric_key(t_matrix **matrix)
{
	matrix[0][0].isometric *= -1;
	if (matrix[0][0].isometric == 1)
	{
		center_key(matrix);
		matrix[0][0].rot_x = -0.52;
		matrix[0][0].rot_y = -0.52;
		matrix[0][0].rot_z = -0;
		matrix[0][0].depth = 1;
	}
	else
		center_key(matrix);
}

void	diagonal_key(t_matrix **matrix)
{
	matrix[0][0].imgs.diagonal *= -1;
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
	if (key == X)
		diagonal_key(matrix);
	if (key == SPACE)
		isometric_key(matrix);
}
