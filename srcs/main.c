/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avialle- <avialle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 16:30:44 by avialle-          #+#    #+#             */
/*   Updated: 2024/03/25 15:58:48 by avialle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	init_proj(t_matrix **matrix)
{
	double	scale_x;
	double	scale_y;

	scale_x = (SCALE_FACTOR * WIDTH) / (DATA.width);
	scale_y = (SCALE_FACTOR * HEIGHT) / (DATA.height);
	// printf("scale_x = %f, scale_y = %f\n", scale_x, scale_y);
	if (scale_x < scale_y)
		DATA.scale = scale_x;
	else
		DATA.scale = scale_y;
	// printf("scale = %f\n", DATA.scale);
	DATA.offset_x = (DATA.width / 2) * DATA.scale
		+ round((WIDTH - (DATA.scale * DATA.width)) / 2);
	DATA.offset_y = (DATA.height / 2) * DATA.scale
		+ round((HEIGHT - (DATA.scale * DATA.height)) / 2);
	DATA.imgs.x_step = 1;
	DATA.imgs.y_step = 1;
}

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
		height_width(file);
	}
	else
		ft_exit("Notice : ./fdf <maps.fdf>", NULL, 0);
}

t_matrix	**init_fdf(char *file, t_matrix **matrix)
{
	int	width;
	int	height;

	height = 0;
	width = 0;
	size_matrix(file, &height, &width);
	matrix = alloc_matrix(height, width);
	set_data(matrix, height, width);
	fill_matrix(file, matrix);
	display_matrix(matrix);
	init_proj(matrix);
	return (matrix);
}

int	main(int ac, char **av)
{
	t_matrix	**matrix;

	matrix = NULL;
	check_args(ac, av[1]);
	matrix = init_fdf(av[1], matrix);
	mlx_key_hook(DATA.win, &key_handler, matrix);
	mlx_hook(DATA.win, 17, 0, &close_win, matrix);
	// frame(matrix);
	mlx_loop_hook(DATA.mlx, frame, matrix);
	mlx_loop(DATA.mlx);
	// free_matrix(matrix, DATA.height);
	return (0);
}
