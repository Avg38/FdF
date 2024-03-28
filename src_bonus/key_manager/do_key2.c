/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_key2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avialle- <avialle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 11:37:52 by avialle-          #+#    #+#             */
/*   Updated: 2024/03/28 11:26:00 by avialle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf_bonus.h"

void	rot_key(int key, t_matrix **matrix)
{
	if (key == W)
		matrix[0][0].rot_x += 0.08;
	if (key == S)
		matrix[0][0].rot_x -= 0.08;
	if (key == A)
		matrix[0][0].rot_y += 0.08;
	if (key == D)
		matrix[0][0].rot_y -= 0.08;
}

void	offset_key(int key, t_matrix **matrix)
{
	if (key == UP)
		matrix[0][0].offset_y -= 10;
	if (key == DOWN)
		matrix[0][0].offset_y += 10;
	if (key == LEFT)
		matrix[0][0].offset_x -= 10;
	if (key == RIGHT)
		matrix[0][0].offset_x += 10;
}

void	scale_key(int key, t_matrix **matrix)
{
	if (key == PLUS && matrix[0][0].scale < SCALE_FACTOR * 1000)
		matrix[0][0].scale += 0.2 * matrix[0][0].scale;
	if (key == MINUS && matrix[0][0].scale >= SCALE_FACTOR)
		matrix[0][0].scale -= 0.2 * abs((int)matrix[0][0].scale) / 2;
}

void	depth_key(int key, t_matrix **matrix)
{
	if (key == UP_Z)
		matrix[0][0].depth += 0.1;
	if (key == DOWN_Z)
		matrix[0][0].depth -= 0.1;
}

void	gradient_key(t_matrix **matrix)
{
	matrix[0][0].imgs.gradient *= -1;
}
