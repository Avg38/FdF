/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avialle- <avialle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 14:55:39 by avialle-          #+#    #+#             */
/*   Updated: 2024/03/28 15:14:57 by avialle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf_bonus.h"

void	init_proj_map(t_matrix **matrix)
{
	int	x;
	int	y;

	y = 0;
	while (y < matrix[0][0].height)
	{
		x = 0;
		while (x < matrix[0][0].width && matrix[y][x].is_valid > 0)
		{
			apply_scaling(&matrix[y][x], matrix);
			if (matrix[0][0].isometric == -1)
				mod_2d(matrix);
			else
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
	while (y < matrix[0][0].height)
	{
		x = 0;
		while (x < matrix[0][0].width && matrix[y][x].is_valid)
		{
			if (matrix[y][x + 1].is_valid)
				draw_line(matrix[0][0].imgs, matrix[y][x], matrix[y][x + 1]);
			if (y + 1 < matrix[0][0].height)
			{
				if (matrix[y + 1][x].is_valid)
					draw_line(matrix[0][0].imgs,
						matrix[y][x], matrix[y + 1][x]);
				if (x + 1 < matrix[0][0].width
					&& matrix[0][0].imgs.diagonal == 1)
					draw_line(matrix[0][0].imgs,
						matrix[y][x], matrix[y + 1][x + 1]);
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
	mlx_put_image_to_window(matrix[0][0].mlx, matrix[0][0].win,
		matrix[0][0].imgs.img, 0, 0);
	return (1);
}
