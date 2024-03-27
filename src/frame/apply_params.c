/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_params.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avialle- <avialle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 14:28:32 by avialle-          #+#    #+#             */
/*   Updated: 2024/03/27 14:29:49 by avialle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"

void	apply_scaling(t_matrix *point, t_matrix **matrix)
{
	point->x_proj = point->x * ceil(DATA.scale);
	point->y_proj = point->y * ceil(DATA.scale);
	point->z_proj = point->z * 0.15 * DATA.scale * DATA.depth;
}

void	apply_offset(t_matrix *point, t_matrix **matrix)
{
	point->x_proj = point->x_proj + DATA.offset_x;
	point->y_proj = point->y_proj + DATA.offset_y;
}

void	apply_isometric(t_matrix *point)
{
	point->x_proj = (point->x_proj - point->y_proj);
	point->y_proj = (point->x_proj + point->y_proj) - point->z_proj;
}

void	mod_2d(t_matrix **matrix)
{
	DATA.rot_x = 0;
	DATA.rot_y = 0;
	DATA.rot_z = 0;
}
