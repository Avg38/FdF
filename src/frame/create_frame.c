/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avialle- <avialle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 14:55:39 by avialle-          #+#    #+#             */
/*   Updated: 2024/03/27 16:10:56 by avialle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"

void	init_proj_map(t_matrix **matrix)
{
	int	x;
	int	y;

	y = 0;
	while (y < DATA.height)
	{
		x = 0;
		while (x < DATA.width && matrix[y][x].is_valid > 0)
		{
			apply_scaling(&matrix[y][x], matrix);
			apply_rotation(&matrix[y][x], matrix);
			apply_offset(&matrix[y][x], matrix);
			x++;
		}
		y++;
	}
}

void	transform_img(t_matrix **matrix)
{
	int	x;
	int	y;

	y = 0;
	while (y < DATA.height)
	{
		x = 0;
		while (x < DATA.width && matrix[y][x].is_valid)
		{
			if (matrix[y][x + 1].is_valid)
				draw_line(DATA.imgs, matrix[y][x], matrix[y][x + 1]);
			if (y + 1 < DATA.height)
			{
				if (matrix[y + 1][x].is_valid)
					draw_line(DATA.imgs, matrix[y][x], matrix[y + 1][x]);
			}
			x++;
		}
		y++;
	}
}

int	frame(t_matrix **matrix)
{
	init_proj_map(matrix);
	transform_img(matrix);
	mlx_put_image_to_window(DATA.mlx, DATA.win, DATA.imgs.img, 0, 0);
	return (1);
}
