/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avialle- <avialle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 16:30:44 by avialle-          #+#    #+#             */
/*   Updated: 2024/03/23 14:28:03 by avialle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	define_scale(t_matrix **matrix)
{
	double	scale_x;
	double	scale_y;

	scale_x = 0.85 * 1200 / (DATA.width);
	scale_y = 0.85 * 1000 / (DATA.height);
	if (scale_x < scale_y)
		DATA.scale = scale_x;
	else
		DATA.scale = scale_y;
}

void	define_offsets(t_matrix **matrix *p_proj, double scale)
{
	DATA.offset_x = md.center_x * DATA.scale
		+ round((DATA.width - (DATA.scale * md.width)) / 2);
	DATA.offset_y = md.center_y * DATA.scale
		+ round((DATA.height - (DATA.scale * md.height)) / 2);
}


void	init_s_projections(t_matrix **matrix)
{
	define_scale(&(projs->current), p_fdf->map_data);
	define_offsets(&(projs->current), p_fdf->map_data, projs->current.scale);
	projs->current.rot_x = -0.52;
	projs->current.rot_y = 0.52;
	projs->current.rot_z = 0;
	projs->current.depthfactor = 1;
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

void	init_fdf(char *file)
{
	t_matrix	**matrix;
	int			width;
	int			height;

	height = 0;
	width = 0;
	size_matrix(file, &height, &width);
	matrix = alloc_matrix(height, width);
	set_data(matrix, height, width);
	fill_matrix(file, matrix);
	display_matrix(matrix);
	init_projections(matrix);
	mlx_key_hook(DATA.win, &key_handler, matrix);
	mlx_hook(DATA.win, DestroyNotify, StructureNotifyMask, &close_win, matrix);
	mlx_loop(DATA.mlx);
	free_matrix(matrix, DATA.height);
}

int	main(int ac, char **av)
{
	check_args(ac, av[1]);
	init_fdf(av[1]);
	return (0);
}
