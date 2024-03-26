/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avialle- <avialle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 13:47:03 by avialle-          #+#    #+#             */
/*   Updated: 2024/03/26 13:57:25 by avialle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

int	strhexa_to_colorint(char *strhexa)
{
	int	i;

	i = 2;
	if (!strhexa)
		return (0xFFFFFFFF);
	if (strncmp("0x", strhexa, 2) != 0)
		ft_exit("Bad format for color", NULL, 0);
	while (strhexa[i] && strhexa[i] != ' ')
	{
		if (strhexa[i] >= 'a' && strhexa[i] <= 'f')
			strhexa[i] -= 32;
		i++;
	}
	return (ft_atoi_base(&strhexa[2], "0123456789ABCDEF"));
}

t_argb	create_argb(int color)
{
	t_argb	argb;
	int		mask;

	mask = 0xFF;
	argb.a = (unsigned char)(color >> 24) & mask;
	argb.r = (unsigned char)(color >> 16) & mask;
	argb.g = (unsigned char)(color >> 8) & mask;
	argb.b = (unsigned char)color & mask;
	return (argb);
}

int	create_color_gradient(float delta, t_argb color1, t_argb color2)
{
	t_argb	new_c;
	int		color_int;

	new_c.a = (1 - delta) * color1.a + delta * color2.a;
	new_c.r = (1 - delta) * color1.r + delta * color2.r;
	new_c.g = (1 - delta) * color1.g + delta * color2.g;
	new_c.b = (1 - delta) * color1.b + delta * color2.b;
	color_int = (new_c.a << 24) + (new_c.r << 16) + (new_c.g << 8) + new_c.b;
	return (color_int);
}

int	process_color(int curr_steps, int tot_steps, int color_ini, int color_end)
{
	float	delta;
	int		c_processed;

	delta = (float) curr_steps / tot_steps;
	c_processed = create_color_gradient(delta,
			create_argb(color_ini), create_argb(color_end));
	return (c_processed);
}
