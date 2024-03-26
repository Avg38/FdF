/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avialle- <avialle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 14:55:39 by avialle-          #+#    #+#             */
/*   Updated: 2024/03/26 16:00:22 by avialle-         ###   ########.fr       */
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

void	apply_rot_x(t_matrix *point, double cos_a, double sin_a)
{
	int	old_y;
	int	old_z;

	old_y = point->y_proj;
	old_z = point->z_proj;
	point->y_proj = old_y * cos_a + old_z * sin_a;
	point->z_proj = old_y * (-sin_a) + old_z * cos_a;
}

void	apply_rot_y(t_matrix *point, double cos_a, double sin_a)
{
	int	old_x;
	int	old_z;

	old_x = point->x_proj;
	old_z = point->z_proj;
	point->x_proj = old_x * cos_a + old_z * (-sin_a);
	point->z_proj = old_x * sin_a + old_z * cos_a;
}

void	apply_rot_z(t_matrix *point, double cos_a, double sin_a)
{
	int	old_x;
	int	old_y;

	old_x = point->x_proj;
	old_y = point->y_proj;
	point->x_proj = old_x * cos_a + old_y * sin_a;
	point->y_proj = old_x * (-sin_a) + old_y * cos_a;
}

void	apply_rotation(t_matrix *point, t_matrix **matrix)
{
	apply_rot_x(point, (double)cos(DATA.rot_x), (double)sin(DATA.rot_x));
	apply_rot_y(point, (double)cos(DATA.rot_y), (double)sin(DATA.rot_y));
	apply_rot_z(point, (double)cos(DATA.rot_z), (double)sin(DATA.rot_z));
}

void	mod_2d(t_matrix **matrix)
{
	DATA.rot_x = 0;
	DATA.rot_y = 0;
	DATA.rot_z = 0;
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
			if (DATA.is_isometric == 0)
				mod_2d(matrix);
			else
			{
				apply_isometric(&matrix[y][x], DATA.angle);
				apply_rotation(&matrix[y][x], matrix);
			}
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
