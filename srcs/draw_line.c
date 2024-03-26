/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avialle- <avialle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 11:51:29 by avialle-          #+#    #+#             */
/*   Updated: 2024/03/26 11:50:12 by avialle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

// void	put_pixel(t_imgs imgs, int x, int y, int color)
// {
// 	int	offset;

// 	offset = (imgs.line_len * y) + (imgs.bits_per_pixel * x / 8);
// 	if (x >= 0 && x < WIDTH && y > 0 && y < HEIGHT)
// 	{
// 		*((int *)(imgs.addr + offset)) = color;
// 	}
// }

// void	draw_acute_slope(t_imgs imgs, t_matrix m0, t_matrix m1)
// {
// 	while (m0.x_proj != m1.x_proj)
// 	{
// 		if (m0.x_proj >= 0 && m0.x_proj < WIDTH && m0.y_proj > 0 && m0.y_proj < HEIGHT)
// 			put_pixel(imgs, m0.x_proj, m0.y_proj, m0.color);
// 		m0.x_proj += imgs.x_step;
// 		if (imgs.decision <= 0)
// 			imgs.decision = 2 * imgs.y_diff;
// 		else
// 		{
// 			m0.y_proj += imgs.y_diff;
// 			imgs.decision = 2 * (imgs.y_diff - imgs.x_diff);
// 		}
// 	}
// }

// void	draw_obtus_slope(t_imgs imgs, t_matrix m0, t_matrix m1)
// {
// 	while (m0.y_proj != m1.y_proj)
// 	{
// 		if (m0.x_proj >= 0 && m0.x_proj < WIDTH && m0.y_proj > 0 && m0.y_proj < HEIGHT)
// 			put_pixel(imgs, m0.x_proj, m0.y_proj, m0.color);
// 		m0.y_proj += imgs.y_step;
// 		if (imgs.decision <= 0)
// 			imgs.decision = 2 * imgs.x_diff;
// 		else
// 		{
// 			m0.x_proj += imgs.x_diff;
// 			imgs.decision = 2 * (imgs.x_diff - imgs.y_diff);
// 		}
// 	}
// }


// void	init_step(t_imgs *imgs, t_matrix m0, t_matrix m1)
// {
// 	imgs->x_diff = abs(m1.x_proj - m0.x_proj);
// 	imgs->y_diff = abs(m1.y_proj - m0.y_proj);
// 	if (m1.x_proj > m0.x_proj)
// 		imgs->x_step = 1;
// 	else
// 		imgs->x_step = -1;
// 	if (m1.y_proj > m0.y_proj)
// 		imgs->y_step = 1;
// 	else
// 		imgs->y_step = -1;
// }

// void	draw_line(t_imgs imgs, t_matrix m0, t_matrix m1)
// {
// 	init_step(&imgs, m0, m1);
// 	if (imgs.x_diff >= imgs.y_diff)
// 	{
// 		imgs.decision = 2 * imgs.y_diff - imgs.x_diff;
// 		ft_printf("x decision = %d\n", imgs.decision);
// 		draw_acute_slope(imgs, m0, m1);
// 	}
// 	else
// 	{
// 		imgs.decision = 2 * imgs.x_diff - imgs.y_diff;
// 		ft_printf("y decision = %d\n", imgs.decision);
// 		draw_obtus_slope(imgs, m0, m1);
// 	}
// }

void	zoom(t_matrix *m1, t_matrix *m2, t_matrix **matrix)
{
	m1->x *= DATA.scale;
	m1->y *= DATA.scale;
	m2->x *= DATA.scale;
	m2->y *= DATA.scale;
	m1->z *= DATA.depth;
	m2->z *= DATA.depth;
}

void	set_param(t_matrix *m1, t_matrix *m2, t_matrix **matrix)
{
	zoom(m1, m2, matrix);
	if (DATA.angle)
	{
		apply_isometric(m1, DATA.angle);
		apply_isometric(m2, DATA.angle);
	}
	m1->x += DATA.offset_x;
	m1->y += DATA.offset_y;
	m2->x += DATA.offset_x;
	m2->y += DATA.offset_y;
}

float	find_max(float a, float b)
{
	if (a > b)
		return (a);
	return (b);
}


void	bresenham(t_matrix m1, t_matrix m2, t_matrix **matrix)
{
	float	step_x;
	float	step_y;
	float	max;

	set_param(&m1, &m2, matrix);
	step_x = m2.x - m1.x;
	step_y = m2.y - m1.y;
	max = find_max(abs(step_x), abs(step_y));
	step_x /= max;
	step_y /= max;
	while ((int)(m1.x - m2.x) || (int)(m1.y - m2.y))
	{
		mlx_pixel_put(DATA.mlx, DATA.win, m1.x, m1.y, 250);
		m1.x += step_x;
		m1.y += step_y;
		if (m1.x > WIDTH || m1.y > HEIGHT || m1.y < 0 || m1.x < 0)
			break;
	}
}

void	print_menu(t_matrix **matrix)
{
	char	*menu;

	menu = "up, down, left, right: move picture";
	mlx_string_put(DATA.mlx, DATA.win, 10, 10, 0xFFFFFF, menu);
	menu = "Space: 3d/2d mode; +, -: zoom";
	mlx_string_put(DATA.mlx, DATA.win, 10, 25, 0xFFFFFF, menu);
	menu = "Page up, pager down: z-scale; *, /: rotation";
	mlx_string_put(DATA.mlx, DATA.win, 10, 40, 0xFFFFFF, menu);
	menu = "f: full screen mode";
	mlx_string_put(DATA.mlx, DATA.win, 10, 55, 0xFFFFFF, menu);
}

void	draw_line(t_matrix **matrix)
{
	int	y;
	int	x;

	print_menu(matrix);
	y = 0;
	while (y < DATA.height)
	{
		x = 0;
		while (1)
		{
			if (matrix[y + 1])
				bresenham(matrix[y][x], matrix[y + 1][x], &DATA);
			if (matrix[y][x].is_valid)
				bresenham(matrix[y][x], matrix[y][x + 1], &DATA);
			if (!matrix[y][x].is_valid)
				break;
			x++;
		}
		y++;
	}
}

// void	draw_line(t_imgs imgs, t_matrix m0, t_matrix m1)
// {
// 	imgs.x_diff = abs(m1.x_proj - m0.x_proj);
// 	imgs.y_diff = abs(m1.y_proj - m0.y_proj);
// 	if (m1.x_proj < m0.x_proj)
// 		imgs.x_step = -1;
// 	if (m1.y_proj < m0.y_proj)
// 		imgs.y_step = -1;
// 	while (1)
// 	{
// 		if (m0.x_proj >= 0 && m0.x_proj < WIDTH && m0.y_proj > 0 && m0.y_proj < HEIGHT)
// 			put_pixel(imgs, m0.x_proj, m0.y_proj, m0.color);
// 		if (m0.x_proj == m1.x_proj && m0.y_proj == m1.y_proj)
// 			break;
// 		if (m0.x_proj != m1.x_proj)
// 			m0.x_proj += imgs.x_step;
// 		if (m0.y_proj != m1.y_proj)
// 			m0.y_proj += imgs.y_step;
// 	}
// }