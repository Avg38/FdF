/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avialle- <avialle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 18:31:00 by avialle-          #+#    #+#             */
/*   Updated: 2024/03/28 14:18:21 by avialle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"

char	**line_parser(char *line)
{
	char	**split;

	if (!line)
		return (NULL);
	split = ft_split(line, ' ');
	if (!split)
		return (NULL);
	free(line);
	return (split);
}

void	display_matrix(t_matrix **matrix)
{
	int	x;
	int	y;

	if (!matrix || !(*matrix) || matrix[0][0].width < 0
		|| matrix[0][0].height < 0)
		ft_exit("Error! display_matrix: matrix is NULL\n",
			matrix, matrix[0][0].height);
	ft_printf(" ");
	x = -1;
	while (++x < matrix[0][0].width)
		(x < 10) ? ft_printf("  %d", x): ft_printf(" %d", x);
	y = -1;
	while (++y < matrix[0][0].height)
	{
		ft_printf("\n%d", y);
		x = -1;
		while (++x < matrix[0][0].width)
		{
			if (!(y >= 10 && x == 0) && matrix[y][x].z < 10)
				ft_printf("  %d", matrix[y][x].z);
			else
				ft_printf(" %d", matrix[y][x].z);
		}
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
