/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_params.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avialle- <avialle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 14:28:32 by avialle-          #+#    #+#             */
/*   Updated: 2024/04/02 11:53:06 by avialle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf_bonus.h"

void	apply_scaling(t_matrix *point, t_matrix **matrix)
{
	point->x_proj = point->x * ceil(matrix[0][0].scale);
	point->y_proj = point->y * ceil(matrix[0][0].scale);
	point->z_proj = point->z * 0.15 * matrix[0][0].scale * matrix[0][0].depth;
}

void	apply_offset(t_matrix *point, t_matrix **matrix)
{
	point->x_proj = point->x_proj + matrix[0][0].offset_x;
	point->y_proj = point->y_proj + matrix[0][0].offset_y;
}
