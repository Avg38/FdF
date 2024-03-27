/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_key2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avialle- <avialle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 11:39:14 by avialle-          #+#    #+#             */
/*   Updated: 2024/03/27 11:41:50 by avialle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	center_key(t_matrix **matrix)
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

void	isometric_key(t_matrix **matrix)
{
	if (DATA.is_isometric == 0)
	{
		DATA.is_isometric = 1;
		center_key(matrix);
		DATA.rot_x = -0.52;
		DATA.rot_y = -0.52;
		DATA.rot_z = -0;
		DATA.depth = 0.1;
	}
	else
	{
		DATA.is_isometric = 0;
		center_key(matrix);
	}
}
