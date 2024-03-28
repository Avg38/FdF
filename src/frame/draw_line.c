/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avialle- <avialle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 11:51:29 by avialle-          #+#    #+#             */
/*   Updated: 2024/03/28 16:05:28 by avialle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"

void	put_pixel(t_imgs imgs, int x, int y, int color)
{
	int	offset;

	offset = (imgs.line_len * y) + (imgs.bits_per_pixel * x / 8);
	if (x >= 0 && x < WIN_W && y > 0 && y < WIN_H)
		*((int *)(imgs.addr + offset)) = color;
}

void	draw_acute_slope(t_imgs imgs, t_matrix p0, t_matrix p1)
{
	int	nb_steps;

	nb_steps = 0;
	while (p0.x_proj != p1.x_proj)
	{
		if (p0.x_proj >= 0 && p0.x_proj < WIN_W
			&& p0.y_proj >= 0 && p0.y_proj < WIN_H)
			put_pixel(imgs, p0.x_proj, p0.y_proj, p0.color);
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

	nb_steps = 0;
	while (p0.y_proj != p1.y_proj)
	{
		if (p0.x_proj >= 0 && p0.x_proj < WIN_W
			&& p0.y_proj >= 0 && p0.y_proj < WIN_H)
			put_pixel(imgs, p0.x_proj, p0.y_proj, p0.color);
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

void	init_step(t_imgs *imgs, t_matrix p0, t_matrix p1)
{
	imgs->x_diff = abs(p1.x_proj - p0.x_proj);
	imgs->y_diff = abs(p1.y_proj - p0.y_proj);
	if (p1.x_proj > p0.x_proj)
		imgs->x_step = 1;
	else
		imgs->x_step = -1;
	if (p1.y_proj > p0.y_proj)
		imgs->y_step = 1;
	else
		imgs->y_step = -1;
}

void	draw_line(t_imgs imgs, t_matrix p0, t_matrix p1)
{
	init_step(&imgs, p0, p1);
	if (imgs.x_diff >= imgs.y_diff)
	{
		imgs.decision = 2 * imgs.y_diff - imgs.x_diff;
		draw_acute_slope(imgs, p0, p1);
	}
	else
	{
		imgs.decision = 2 * imgs.x_diff - imgs.y_diff;
		draw_obtus_slope(imgs, p0, p1);
	}
}
