/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_key.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avialle- <avialle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 11:37:52 by avialle-          #+#    #+#             */
/*   Updated: 2024/03/27 11:41:57 by avialle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

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

void	do_key(int key, t_matrix **matrix)
{
	if (key == W || key == S || key == A || key == D)
		rot_key(key, matrix);
	if (key == UP || key == DOWN || key == LEFT || key == RIGHT)
		offset_key(key, matrix);
	if (key == PLUS || key == MINUS)
		scale_key(key, matrix);
	if (key == UP || key == DOWN)
		depth_key(key, matrix);
	if (key == C)
		center_key(matrix);
	if (key == G)
		gradient_key(key, matrix);
	if (key == SPACE)
		isometric_key(matrix);
}
