/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avialle- <avialle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 17:00:19 by avialle-          #+#    #+#             */
/*   Updated: 2024/02/26 10:28:33 by avialle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	display_matrix(t_map **matrix, int height, int width)
{
	int	y;
	int	x;

	y = 0;
	x = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			ft_printf("matrix[%d][%d].y = %d\n", y, x, matrix[y][x].y);
			ft_printf("matrix[%d][%d].x = %d\n", y, x, matrix[y][x].x);
			ft_printf("matrix[%d][%d].z = %d\n", y, x, matrix[y][x].z);
			ft_printf("matrix[%d][%d].color = %d\n", y, x, matrix[y][x].color);
			x++;
		}
		ft_printf("\n");
		y++;
	}
}

void	display_tab2d(char **s, int height)
{
	int	i;

	i = -1;
	if (s)
		while (++i < height)
			ft_printf("%s", s[i]);
}
