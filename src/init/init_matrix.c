/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_matrix.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avialle- <avialle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 15:56:19 by avialle-          #+#    #+#             */
/*   Updated: 2024/03/27 16:29:59 by avialle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"

void	init_proj(t_matrix **matrix)
{
	double	scale_x;
	double	scale_y;

	scale_x = (SCALE_FACTOR * WIDTH) / (DATA.width);
	scale_y = (SCALE_FACTOR * HEIGHT) / (DATA.height);
	if (scale_x < scale_y)
		DATA.scale = scale_x;
	else
		DATA.scale = scale_y;
	DATA.offset_x = (WIDTH - DATA.width * DATA.scale) / 2;
	DATA.offset_y = (HEIGHT - DATA.height * DATA.scale) / 2;
	DATA.imgs.x_step = 1;
	DATA.imgs.y_step = 1;
	DATA.rot_x = -0.52;
	DATA.rot_y = -0.52;
	DATA.rot_z = -0;
	DATA.depth = 1;
}

t_imgs	init_new_img(t_matrix	**matrix)
{
	t_imgs	img;

	ft_bzero(&img, sizeof(t_imgs));
	img.img = mlx_new_image(DATA.mlx, WIDTH, HEIGHT);
	if (!img.img)
		ft_exit("Error, init_new_image", matrix, DATA.height);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
			&img.line_len, &img.endian);
	if (!img.addr)
		ft_exit("Error, init_new_image", matrix, DATA.height);
	return (img);
}

void	init_data(t_matrix **matrix, int height, int width)
{
	DATA.height = height;
	DATA.width = width;
	DATA.mlx = mlx_init();
	if (!DATA.mlx)
		ft_exit("Error DATA.mlx\n", matrix, DATA.height);
	DATA.win = mlx_new_window(DATA.mlx, WIDTH, HEIGHT, "FDF");
	if (!DATA.win)
		ft_exit("Error DATA.win\n", matrix, DATA.height);
	DATA.imgs = init_new_img(matrix);
	if (mlx_put_image_to_window(DATA.mlx, DATA.win, DATA.imgs.img, 0, 0) < 0)
		ft_exit("Error mlx_put_img_to_win\n", matrix, DATA.height);
}



t_matrix	**alloc_matrix(int height, int width)
{
	t_matrix	**matrix;
	int			y;
	int			x;

	matrix = (t_matrix **)malloc(height * sizeof(t_matrix *));
	if (!matrix)
		return (ft_exit("malloc matrix failed", NULL, 0), NULL);
	y = -1;
	while (++y < height)
	{
		matrix[y] = (t_matrix *)malloc((width + 1) * sizeof(t_matrix));
		if (!matrix[y])
			return (ft_exit("malloc matrix element failed", matrix, y), NULL);
	}
	y = -1;
	while (++y < height)
	{
		x = -1;
		while (++x <= width)
			fill_zero(&matrix[y][x]);
	}
	return (matrix);
}
