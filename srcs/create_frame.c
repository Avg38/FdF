/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avialle- <avialle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 14:55:39 by avialle-          #+#    #+#             */
/*   Updated: 2024/03/25 16:51:34 by avialle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	apply_scaling(t_matrix *point, t_matrix **matrix)
{
	point->x_proj = point->x * ceil(DATA.scale);
	point->y_proj = point->y * ceil(DATA.scale);
	point->z_proj = point->z * 1 * DATA.scale * DATA.depth;
}

void	apply_offset(t_matrix *point, t_matrix **matrix)
{
	point->x_proj = point->x_proj + DATA.offset_x;
	point->y_proj = point->y_proj + DATA.offset_y;
}


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
			// ft_printf("1: x_proj = %d\n", matrix[y][x].x_proj);
			apply_scaling(&matrix[y][x], matrix);
			// ft_printf("2: x_proj = %d\n", matrix[y][x].x_proj);
			apply_offset(&matrix[y][x], matrix);
			// ft_printf("3: x_proj = %d\n", matrix[y][x].x_proj);
			x++;
		}
		y++;
	}
	// exit(EXIT_FAILURE);
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
			if (x + 1 < DATA.width || matrix[y][x + 1].is_valid)
				draw_line(DATA.imgs, matrix[y][x], matrix[y][x + 1]);
			if (y + 1 < DATA.height)
				draw_line(DATA.imgs, matrix[y][x], matrix[y + 1][x]);
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
