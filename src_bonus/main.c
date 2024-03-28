/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avialle- <avialle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 16:30:44 by avialle-          #+#    #+#             */
/*   Updated: 2024/03/28 15:31:46 by avialle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf_bonus.h"

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
	mlx_hook(matrix[0][0].win, 2, 1L << 0, &key_handler, matrix);
	mlx_hook(matrix[0][0].win, 17, (1L << 17), &close_win, matrix);
	mlx_loop_hook(matrix[0][0].mlx, frame, matrix);
	mlx_loop(matrix[0][0].mlx);
	return (0);
}
