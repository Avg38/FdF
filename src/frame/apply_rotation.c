/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_rotation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avialle- <avialle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 14:27:24 by avialle-          #+#    #+#             */
/*   Updated: 2024/04/02 15:22:57 by avialle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"

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
	apply_rot_x(point, (double)cos(matrix[0][0].rot_x),
		(double)sin(matrix[0][0].rot_x));
	apply_rot_y(point, (double)cos(matrix[0][0].rot_y),
		(double)sin(matrix[0][0].rot_y));
	apply_rot_z(point, (double)cos(matrix[0][0].rot_z),
		(double)sin(matrix[0][0].rot_z));
}
