/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avialle- <avialle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 16:30:44 by avialle-          #+#    #+#             */
/*   Updated: 2024/03/22 16:47:41 by avialle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

int	on_destroy(t_matrix **matrix)
{
	mlx_destroy_window(DATA.mlx, DATA.win);
	mlx_destroy_display(DATA.mlx);
	free(DATA.mlx);
	free_matrix(matrix, DATA.height);
	exit (EXIT_SUCCESS);
	return (0);
}

int	is_key(int key)
{
	return (key == UP || key == DOWN || key == LEFT || key == RIGHT || key == SPACE
		|| key == MINUS || key == PLUS || key == STAR || key == DIV
		|| key == UP_Z || key == DOWN_Z);
}

void	do_key(int key, t_matrix **matrix)
{
	if (key == PLUS)
		DATA.scale += 3;
	if (key == MINUS)
		DATA.scale -= 3;
	if (key == STAR)
		DATA.angle += 0.05;
	if (key == DIV)
		DATA.angle -= 0.05;
}

int	key_handler(int key, t_matrix **matrix)
{
	printf("key = %d\n", key);
	if (is_key(key))
	{
		mlx_clear_window(DATA.mlx, DATA.win);
		do_key(key, matrix);
	}
	if (key == ESC)
		on_destroy(matrix);
	return (0);
}

void	init_fdf(char *file)
{
	t_matrix	**matrix;
	int			width;
	int			height;

	height = 0;
	width = 0;
	size_matrix(file, &height, &width);
	matrix = alloc_matrix(height, width);
	set_DATA(matrix, height, width);
	fill_matrix(file, matrix);
	display_matrix(matrix);
	mlx_key_hook(DATA.win, &key_handler, matrix);
	mlx_hook(DATA.win, DestroyNotify, StructureNotifyMask, &on_destroy, matrix);
	mlx_loop(DATA.mlx);
	free_matrix(matrix, DATA.height);
}

int	main(int ac, char **av)
{
	check_args(ac, av[1]);
	init_fdf(av[1]);
	return (0);
}
