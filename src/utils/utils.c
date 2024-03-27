/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avialle- <avialle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 18:31:00 by avialle-          #+#    #+#             */
/*   Updated: 2024/03/27 16:25:13 by avialle-         ###   ########.fr       */
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

	ft_printf("--\nwidth = %d, height = %d\n--\n", DATA.width, DATA.height);
	if (!matrix || !(*matrix) || DATA.width < 0 || DATA.height < 0)
		ft_exit("Error! display_matrix: matrix is NULL\n", matrix, DATA.height);
	ft_printf(" ");
	x = -1;
	while (++x < DATA.width)
		(x < 10) ? ft_printf("  %d", x): ft_printf(" %d", x);
	y = -1;
	while (++y < DATA.height)
	{
		ft_printf("\n%d", y);
		x = -1;
		while (++x < DATA.width)
		{
			if (!(y >= 10 && x == 0) && matrix[y][x].z < 10)
				ft_printf("  %d", matrix[y][x].z);
			else
				ft_printf(" %d", matrix[y][x].z);
		}
	}
	ft_printf("\n--\n");
}

void	display_tab2d(char **s, int height)
{
	int	i;

	i = -1;
	if (s)
		while (++i < height)
			ft_printf("%s", s[i]);
}


