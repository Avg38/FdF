/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_matrix.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avialle- <avialle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 15:56:19 by avialle-          #+#    #+#             */
/*   Updated: 2024/03/28 16:18:16 by avialle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf_bonus.h"

void	init_proj(t_matrix **matrix)
{
	double	scale_x;
	double	scale_y;

	scale_x = (SCALE_FACTOR * WIN_W) / (matrix[0][0].width);
	scale_y = (SCALE_FACTOR * WIN_H) / (matrix[0][0].height);
	if (scale_x < scale_y)
		matrix[0][0].scale = scale_x;
	else
		matrix[0][0].scale = scale_y;
	matrix[0][0].isometric = 1;
	matrix[0][0].imgs.gradient = 1;
	matrix[0][0].imgs.diagonal = 1;
	matrix[0][0].offset_x = (WIN_W - matrix[0][0].width
			* matrix[0][0].scale) / 2;
	matrix[0][0].offset_y = (WIN_H - matrix[0][0].height
			* matrix[0][0].scale) / 2;
	matrix[0][0].imgs.x_step = 1;
	matrix[0][0].imgs.y_step = 1;
	matrix[0][0].rot_x = -0.52;
	matrix[0][0].rot_y = -0.52;
	matrix[0][0].rot_z = -0;
	matrix[0][0].depth = 1;
}

t_imgs	init_new_img(t_matrix	**matrix)
{
	t_imgs	img;

	ft_bzero(&img, sizeof(t_imgs));
	img.img = mlx_new_image(matrix[0][0].mlx, WIN_W, WIN_H);
	if (!img.img)
		ft_exit("Error, init_new_image", matrix, matrix[0][0].height);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
			&img.line_len, &img.endian);
	if (!img.addr)
		ft_exit("Error, init_new_image", matrix, matrix[0][0].height);
	return (img);
}

void	init_data(t_matrix **matrix, int height, int width)
{
	matrix[0][0].height = height;
	matrix[0][0].width = width;
	matrix[0][0].mlx = mlx_init();
	if (!matrix[0][0].mlx)
		ft_exit("Error matrix[0][0].mlx\n", matrix, matrix[0][0].height);
	matrix[0][0].win = mlx_new_window(matrix[0][0].mlx, WIN_W, WIN_H, "FDF");
	if (!matrix[0][0].win)
		ft_exit("Error matrix[0][0].win\n", matrix, matrix[0][0].height);
	matrix[0][0].imgs = init_new_img(matrix);
	if (mlx_put_image_to_window(matrix[0][0].mlx,
		matrix[0][0].win, matrix[0][0].imgs.img, 0, 0) < 0)
		ft_exit("Error mlx_put_img_to_win\n", matrix, matrix[0][0].height);
}

t_matrix	**alloc_matrix(int height, int width)
{
	t_matrix	**matrix;
	int			y;

	matrix = (t_matrix **)ft_calloc(height, sizeof(t_matrix *));
	if (!matrix)
		return (ft_exit("malloc matrix failed", NULL, 0), NULL);
	y = -1;
	while (++y < height)
	{
		matrix[y] = (t_matrix *)ft_calloc(width + 1, sizeof(t_matrix));
		if (!matrix[y])
			return (ft_exit("malloc matrix element failed", matrix, y), NULL);
	}
	y = -1;
	return (matrix);
}

t_matrix	**init_fdf(char *file, t_matrix **matrix)
{
	int	width;
	int	height;

	height = 0;
	width = 0;
	size_matrix(file, &height, &width);
	matrix = alloc_matrix(height, width);
	init_data(matrix, height, width);
	fill_matrix(file, matrix);
	init_proj(matrix);
	return (matrix);
}
