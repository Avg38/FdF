/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avialle- <avialle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 16:30:44 by avialle-          #+#    #+#             */
/*   Updated: 2024/03/28 16:04:53 by avialle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

// void	display_matrix(t_matrix **matrix)
// {
// 	int	x;
// 	int	y;

// 	if (!matrix || !(*matrix) || matrix[0][0].width < 0
// 		|| matrix[0][0].height < 0)
// 		ft_exit("Error! display_matrix: matrix is NULL\n",
// 			matrix, matrix[0][0].height);
// 	ft_printf(" ");
// 	x = -1;
// 	while (++x < matrix[0][0].width)
// 		(x < 10) ? ft_printf("  %d", x): ft_printf(" %d", x);
// 	y = -1;
// 	while (++y < matrix[0][0].height)
// 	{
// 		ft_printf("\n%d", y);
// 		x = -1;
// 		while (++x < matrix[0][0].width)
// 		{
// 			if (!(y >= 10 && x == 0) && matrix[y][x].z < 10)
// 				ft_printf("  %d", matrix[y][x].z);
// 			else
// 				ft_printf(" %d", matrix[y][x].z);
// 		}
// 	}
// }

void	check_args(int ac, char *file)
{
	int	fd;

	if (ac == 2)
	{
		if (!ft_strnstr(file, ".fdf", 4))
			ft_exit("Error! \".fdf\" is needed", NULL, 0);
		fd = open(file, O_RDONLY);
		if (fd < 1)
			ft_exit("Error! Bad fd or file empty", NULL, 0);
		close(fd);
	}
	else
		ft_exit("Notice : ./fdf <maps.fdf>", NULL, 0);
}

int	main(int ac, char **av)
{
	t_matrix	**matrix;

	matrix = NULL;
	check_args(ac, av[1]);
	matrix = init_fdf(av[1], matrix);
	mlx_key_hook(matrix[0][0].win, &esc_handler, matrix);
	mlx_hook(matrix[0][0].win, 17, 1L << 17, &close_win, matrix);
	frame(matrix);
	mlx_loop(matrix[0][0].mlx);
	return (0);
}
