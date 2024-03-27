/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avialle- <avialle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 11:51:29 by avialle-          #+#    #+#             */
/*   Updated: 2024/03/27 10:29:49 by avialle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	put_pixel(t_imgs imgs, int x, int y, int color)
{
	int	offset;

	offset = (imgs.line_len * y) + (imgs.bits_per_pixel * x / 8);
	if (x >= 0 && x < WIDTH && y > 0 && y < HEIGHT)
		*((int *)(imgs.addr + offset)) = color;
}


void	draw_acute_slope(t_imgs imgs, t_matrix p0, t_matrix p1)
{
	int	nb_steps;
	int	gradient;

	nb_steps = 0;
	while (p0.x_proj != p1.x_proj)
	{
		if (p0.color != p1.color && imgs.is_gradient == 1)
			gradient = process_color(nb_steps, imgs.x_diff, p0.color, p1.color);
		else
			gradient = p0.color;
		if (p0.x_proj >= 0 && p0.x_proj < WIDTH
			&& p0.y_proj >= 0 && p0.y_proj < HEIGHT)
			put_pixel(imgs, p0.x_proj, p0.y_proj, gradient);
		p0.x_proj += imgs.x_step;
		if (imgs.decision <= 0)
			imgs.decision += 2 * imgs.y_diff;
		else
		{
			p0.y_proj += imgs.y_step;
			imgs.decision += 2 * (imgs.y_diff - imgs.x_diff);
		}
		nb_steps++;
	}
}

void	draw_obtus_slope(t_imgs imgs, t_matrix p0, t_matrix p1)
{
	int	nb_steps;
	int	gradient;

	nb_steps = 0;
	while (p0.y_proj != p1.y_proj)
	{
		if (p0.color != p1.color && imgs.is_gradient == 1)
			gradient = process_color(nb_steps, imgs.y_diff, p0.color, p1.color);
		else
			gradient = p0.color;
		if (p0.x_proj >= 0 && p0.x_proj < WIDTH
			&& p0.y_proj >= 0 && p0.y_proj < HEIGHT)
			put_pixel(imgs, p0.x_proj, p0.y_proj, gradient);
		p0.y_proj += imgs.y_step;
		if (imgs.decision <= 0)
			imgs.decision += 2 * imgs.x_diff;
		else
		{
			p0.x_proj += imgs.x_step;
			imgs.decision += 2 * (imgs.x_diff - imgs.y_diff);
		}
		nb_steps++;
	}
}


void	init_step(t_imgs *imgs, t_matrix m0, t_matrix m1)
{
	imgs->x_diff = abs(m1.x_proj - m0.x_proj);
	imgs->y_diff = abs(m1.y_proj - m0.y_proj);
	if (m1.x_proj > m0.x_proj)
		imgs->x_step = 1;
	else
		imgs->x_step = -1;
	if (m1.y_proj > m0.y_proj)
		imgs->y_step = 1;
	else
		imgs->y_step = -1;
}

void	draw_line(t_imgs imgs, t_matrix m0, t_matrix m1)
{
	init_step(&imgs, m0, m1);
	if (imgs.x_diff >= imgs.y_diff)
	{
		imgs.decision = 2 * imgs.y_diff - imgs.x_diff;
		draw_acute_slope(imgs, m0, m1);
	}
	else
	{
		imgs.decision = 2 * imgs.x_diff - imgs.y_diff;
		draw_obtus_slope(imgs, m0, m1);
	}
}
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
// 		if ((m0.x_proj >= 0 && m0.x_proj < WIDTH) || (m0.y_proj >= 0 && m0.y_proj < HEIGHT))
// 			put_pixel(imgs, m0.x_proj, m0.y_proj, m0.color);
// 		if (m0.x_proj == m1.x_proj && m0.y_proj == m1.y_proj)
// 			break;
// 		if (m0.x_proj != m1.x_proj)
// 			m0.x_proj += imgs.x_step;
// 		if (m0.y_proj != m1.y_proj)
// 			m0.y_proj += imgs.y_step;
// 	}
// }

// void	draw_line_y(t_imgs imgs, t_matrix m0, t_matrix m1)
// {
// 	imgs.x_diff = abs(m1.x_proj - m0.x_proj);
// 	imgs.y_diff = abs(m1.y_proj - m0.y_proj);
// 	if (m1.x_proj < m0.x_proj)
// 		imgs.x_step = -1;
// 	if (m1.y_proj < m0.y_proj)
// 		imgs.y_step = -1;
// 	while (1)
// 	{
// 		if (m0.x_proj >= 0 && m0.x_proj < WIDTH && m0.y_proj >= 0 && m0.y_proj < HEIGHT)
// 			put_pixel(imgs, m0.x_proj, m0.y_proj, m0.color);
// 		if (m0.x_proj == m1.x_proj && m0.y_proj == m1.y_proj)
// 			break;
// 		if (m0.x_proj != m1.x_proj)
// 			m0.x_proj += imgs.x_step;
// 		if (m0.y_proj != m1.y_proj)
// 			m0.y_proj += imgs.y_step;
// 	}
// }