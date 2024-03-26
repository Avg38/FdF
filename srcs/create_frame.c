/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avialle- <avialle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 14:55:39 by avialle-          #+#    #+#             */
/*   Updated: 2024/03/26 11:32:50 by avialle-         ###   ########.fr       */
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


void	apply_isometric(t_matrix *point, double angle)
{
	point->x_proj = (point->x_proj - point->y_proj) * cos(angle);
	point->y_proj = (point->x_proj + point->y_proj) * sin(angle) - point->z_proj;
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
			apply_scaling(&matrix[y][x], matrix);
			apply_isometric(&matrix[y][x], DATA.angle);
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
				if (matrix[y + 1][x].is_valid)
					draw_line(DATA.imgs, matrix[y][x], matrix[y + 1][x]);
			x++;
		}
		ft_printf("blabla\n");
		y++;
	}
}



int	frame(t_matrix **matrix)
{
	init_proj_map(matrix);
	transform_img(matrix);
	ft_printf("1\n");
	mlx_put_image_to_window(DATA.mlx, DATA.win, DATA.imgs.img, 0, 0);
	return (1);
}
