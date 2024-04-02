/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avialle- <avialle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 13:47:03 by avialle-          #+#    #+#             */
/*   Updated: 2024/04/02 16:30:33 by avialle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf_bonus.h"

t_rgb	create_argb(int color)
{
	t_rgb	rgb;
	int		mask;

	mask = 0xFF;
	rgb.r = (unsigned char)(color >> 16) & mask;
	rgb.g = (unsigned char)(color >> 8) & mask;
	rgb.b = (unsigned char)color & mask;
	return (rgb);
}

int	create_color_gradient(float delta, t_rgb color1, t_rgb color2)
{
	t_rgb	new_c;
	int		color_int;

	new_c.r = (1 - delta) * color1.r + delta * color2.r;
	new_c.g = (1 - delta) * color1.g + delta * color2.g;
	new_c.b = (1 - delta) * color1.b + delta * color2.b;
	color_int = (new_c.r << 16) + (new_c.g << 8) + new_c.b;
	return (color_int);
}

int	process_color(int curr_steps, int tot_steps, int start_color, int end_color)
{
	float	delta;
	int		final_color;

	delta = (float) curr_steps / tot_steps;
	final_color = create_color_gradient(delta,
			create_argb(start_color), create_argb(end_color));
	return (final_color);
}
