/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avialle- <avialle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 16:30:44 by avialle-          #+#    #+#             */
/*   Updated: 2024/02/23 19:18:09 by avialle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"



void	fdf(char *file)
{
	t_map	**matrix;
	int		width;
	int		height;
	int		fd;
	int		y;

	set_size_matrix(&matrix, file, &width, &height);
	if (height < 0 || width < 0)
		return ;
	ft_printf("height = %d, width = %d\n", height, width);
	if (!matrix)
		return ;
	fd = open(file, O_RDONLY);
	y = 0;
	while (y < height)
		fill_matrix(line_parser(get_next_line(fd)), &matrix, width, &y);
	close(fd);
	display_matrix(matrix, height, width);
}

int	main(int ac, char **av)
{
	if (ac == 2 && av[1][0] && ft_strnstr(av[1], ".fdf", 4))
		fdf(av[1]);
	return (0);
}
