/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avialle- <avialle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 17:00:19 by avialle-          #+#    #+#             */
/*   Updated: 2024/03/22 15:28:31 by avialle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	display_matrix(t_matrix **matrix)
{
	int	y;
	int	x;

	y = 0;
	x = 0;
	while (y < DATA.height)
	{
		x = 0;
		while (x < DATA.width)
		{
			ft_printf("matrix[%d][%d].y = %d\n", y, x, matrix[y][x].y);
			ft_printf("matrix[%d][%d].x = %d\n", y, x, matrix[y][x].x);
			ft_printf("matrix[%d][%d].z = %d\n", y, x, matrix[y][x].z);
			ft_printf("matrix[%d][%d].color = %d\n", y, x, matrix[y][x].color);
			ft_printf("matrix[%d][%d].is_valid = %d\n", y, x, matrix[y][x].is_valid);
			x++;
		}
		if (y == DATA.height)
			break;
		ft_printf("matrix[%d][%d].y = %d\n", y, x, matrix[y][x].y);
		ft_printf("matrix[%d][%d].x = %d\n", y, x, matrix[y][x].x);
		ft_printf("matrix[%d][%d].z = %d\n", y, x, matrix[y][x].z);
		ft_printf("matrix[%d][%d].color = %d\n", y, x, matrix[y][x].color);
		ft_printf("matrix[%d][%d].is_valid = %d\n", y, x, matrix[y][x].is_valid);
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
